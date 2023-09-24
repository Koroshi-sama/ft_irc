#include "command.hpp"

std::string	reply(std::string client_nickname,
				std::string command,
				std::string parameter) {
	return ":" + client_nickname +
			" " + command + " " +
			parameter + "\r\n";
}

bool	check_key_error(ircserv* serv, std::vector<std::string> &vc,
						int client_socket) {

	(void)client_socket;
	if (!serv->_channels[vc[1]]->get_key_bool())
		return true;
/*// 	else if (vc.size() == 2)
// 		send(client_socket, ERR_PASSWDMISMATCH (464), sizeof(), 0);
// 	else if (vc.size() == 3 && \
			serv->_channels[vc[1]]->get_key().compare(vc[2]) != 0)
// 		send(client_socket, ERR_PASSWDMISMATCH (464),\
				sizeof(ERR_NEEDMOREPARAMS), 0);
// 	if (vc.size() == 3 &&\
		serv->_channels[vc[1]]->get_key().strcmp(vc[2]) == 0) {
// 		// SUCCESS
// 		// add member and send message to every member in the channel
// 		return true;
// 	}
*/
	return true;   // just for now
}

void	create_chan_add_cl(ircserv *serv, std::string chan, int client_s) {
// 	int	target_s;
	std::string	reply;

	serv->_channels.insert(std::pair<std::string, Channel*>(chan, new Channel(chan)));
	serv->_channels[chan]->_members.push_back(*serv->_clients[client_s]);
	serv->_channels[chan]->_operators_n = 1;
	serv->_clients[client_s]->set_channel(chan);

	reply = "\r\n:" + serv->_clients[client_s]->get_nickname() +
			" JOIN " + chan + "\r\n";
	command_message(*serv, client_s, "JOIN", chan);
}

void	send_members_list(ircserv* serv, std::string chan, int client_s) {
	std::string		reply;
	std::string		param;
	unsigned int	op_n;

	op_n = serv->_channels[chan]->_operators_n;
	// "=" char denotes that the channel is public, when it's not?
	param = "= " + chan + " :";
	for (unsigned int i = 0; i < op_n; i++)
		param += "@" + serv->_channels[chan]->_members[i].get_nickname();
	for (unsigned int i = op_n; i < serv->_channels[chan]->_members.size(); i++)
		param += " " + serv->_channels[chan]->_members[i].get_nickname();
	numerical_message(*serv, client_s, 353, param);

	param = chan + " :End of /NAMES list.";
	numerical_message(*serv, client_s, 366, param);
}

bool	check_join_req(ircserv& serv, std::vector<std::string> &vc, int client_s) {
	std::vector<std::string>			channels;
	std::vector<std::string>::iterator	it;

// 	if (serv._channels[vc[1]]->is_channel_full())
		// send error
	channels = serv._clients[client_s]->invited_channels;

	std::cout << "Channels client is invited to: ";
	for (size_t i = 0; i < channels.size(); i++)
		std::cout << channels[i] << "  ";
	std::cout << std::endl;

	it = std::find(channels.begin(), channels.end(), vc[1]);
	if (serv._channels[vc[1]]->get_invite_bool() &&
		it == channels.end()) {
			numerical_message(serv, client_s, 473,
								vc[1] + " :Cannot join channel (+i)");
			return false;
	}
	return true;
}

void	Command::join(std::vector<std::string> &vc, int client_socket) {
// 	int			target_s;
	std::string	msg;
	Client		client;
	std::string	chan_topic;

	if (vc.size() == 1 || vc.size() > 3)
		std::cout << "Not enough parameters or too many paramaters\n";
	if (vc.size() == 2 || vc.size() == 3) {
		if (vc[1].find(',') != std::string::npos ||
				(vc.size() == 3 && vc[2].find(',') != std::string::npos)) {
			std::cout << "We will ignore this req. You can't join multiple \
					   channels at the same time or issue multiple passwords\n";
		}
		else {
			if (this->_ircserv->_channels.find(vc[1]) ==
				this->_ircserv->_channels.end()) {
				// create channel and add user (operator)
				create_chan_add_cl(this->_ircserv, vc[1], client_socket);
				chan_topic = _ircserv->_channels[vc[1]]->get_topic();
				if (!chan_topic.empty())
					numerical_message(*_ircserv, client_socket, 332, 
										vc[1] + " :" + chan_topic);
				send_members_list(this->_ircserv, vc[1],  client_socket);
			}
			else {
				// channel exists
				if (!check_join_req(*this->_ircserv, vc, client_socket))
					return ;
				if (check_key_error(this->_ircserv, vc, client_socket)) {
					client = *this->_ircserv->_clients[client_socket];
					this->_ircserv->_channels[vc[1]]->_members.push_back(client);
					this->_ircserv->_clients[client_socket]->set_channel(vc[1]);
					// SUCCESS
					msg = "\r\n:" + client.get_nickname() + " JOIN " 
							+ ":" + vc[1] + "\r\n";
					forward_to_chan(*_ircserv, vc[1], msg, client_socket, true);
					chan_topic = _ircserv->_channels[vc[1]]->get_topic();
					if (!chan_topic.empty())
						numerical_message(*_ircserv, client_socket, 332, 
											vc[1] + " :" + chan_topic);
					// maybe should also send the time of topic creation?
					send_members_list(this->_ircserv, vc[1],  client_socket);
				}
			}
		}
	}
}
