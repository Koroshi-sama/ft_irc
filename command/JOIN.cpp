#include "command.hpp"
// check whether the client can join the channel or not
// 		check the user limit
// 		check the key provided if the channel has a key            a key is a password set by the operator
//
// send the messages that have to be send to every member of the channel upon the successful joinment of a new member

// ---------------------------------------------------------------------------------------

std::string	reply(std::string client_nickname, std::string command, std::string parameter) {
	return ":" + client_nickname + " " + command + " " + parameter + "\r\n";
}

bool	check_key_error(ircserv* serv, std::vector<std::string> &vc, int client_socket) {
	(void)client_socket;
	if (!serv->_channels[vc[1]]->get_key_bool())
		return true;
// 	else if (vc.size() == 2)
// 		send(client_socket, ERR_PASSWDMISMATCH (464), sizeof(), 0);
// 	else if (vc.size() == 3 && serv->_channels[vc[1]]->get_key().compare(vc[2]) != 0)
// 		send(client_socket, ERR_PASSWDMISMATCH (464), sizeof(ERR_NEEDMOREPARAMS), 0);
// 	if (vc.size() == 3 && serv->_channels[vc[1]]->get_key().strcmp(vc[2]) == 0) {
// 		// SUCCESS
// 		// add member and send message to every member in the channel
// 		return true;
// 	}
	return true;   // just for now
}

void	create_chan_add_cl(ircserv *serv, std::string chan, int client_s) {
	int	target_s;
	std::string	reply;

	serv->_channels.insert(std::pair<std::string, Channel*>(chan, new Channel(chan)));
	serv->_channels[chan]->_members.push_back(*serv->_clients[client_s]);
	serv->_channels[chan]->_operators_n = 1;

	reply = "\r\n:" + serv->_clients[client_s]->get_nickname() + " JOIN " + chan + "\r\n";
	target_s = client_s;
	if (send(target_s, reply.c_str(), reply.size() + 1, 0) < 0)
		std::cout << "JOIN MESSAGE IS NOT SENT TO THE ONLY MEMBER OF THE CHANNEL\n";
	else {std::cout << "JOIN MESSAGE IS SENT TO THE ONLY MEMBER OF THE CHANNEL\n";}
}

void	send_members_list(ircserv* serv, std::string chan, int client_s) {
	std::string	reply;

	// "=" char denotes that the channel is public, when it's not?
	reply = "353\r\n:" + serv->_clients[client_s]->get_hostname() + " 353 " + serv->_clients[client_s]->get_nickname() + " = " + chan + " :";
	std::cout << "{" << serv->_clients[client_s]->get_hostname() << "}\n";
	reply += "@" + serv->_channels[chan]->_members[0].get_nickname();
	for (unsigned int i = 1; i < serv->_channels[chan]->_members.size(); i++)
		reply += " " + serv->_channels[chan]->_members[i].get_nickname();
	reply += "\r\n";
	send(client_s, reply.c_str(), reply.size() + 1, 0);
	reply = "366\r\n:" + serv->_clients[client_s]->get_hostname() + " 366 " + serv->_clients[client_s]->get_nickname() + " " + chan + " :End of /NAMES list.\r\n";
	send(client_s, reply.c_str(), reply.size() + 1, 0);
}

void	Command::join(std::vector<std::string> &vc, int client_socket) {
	int			target_s;
	std::string	reply;

	if (vc.size() == 1 || vc.size() > 3)
		std::cout << "Not enough parameters or too many paramaters\n";
	if (vc.size() == 2 || vc.size() == 3) {
		if (vc[1].find(',') != std::string::npos || (vc.size() == 3 && vc[2].find(',') != std::string::npos)) {
			std::cout << "We will ignore this req. You can't join multiple channels at the same time or issue multiple passwords\n";
		}
		else {
			if (this->_ircserv->_channels.find(vc[1]) == this->_ircserv->_channels.end()) {
				// create channel and add user       // later enable this user to be an operator
				create_chan_add_cl(this->_ircserv, vc[1], client_socket);
				send_members_list(this->_ircserv, vc[1],  client_socket);
			}
			else {
				// channel exists
				if (this->_ircserv->_channels[vc[1]]->is_channel_full())
					// send error
				if (this->_ircserv->_channels[vc[1]]->get_invite_bool()) {
					// send error
				}
				if (check_key_error(this->_ircserv, vc, client_socket)) {
					this->_ircserv->_channels[vc[1]]->_members.push_back(*this->_ircserv->_clients[client_socket]);
					// SUCCESS
					for (std::vector<Client>::iterator it = this->_ircserv->_channels[vc[1]]->_members.begin();\
					it != this->_ircserv->_channels[vc[1]]->_members.end(); it++) {
						reply = "\r\n:" + this->_ircserv->_clients[client_socket]->get_nickname() + " JOIN " + ":" + vc[1] + "\r\n";
						target_s = target_socket(it->get_nickname(), this->_ircserv->_clients);
						if (send(target_s, reply.c_str(), reply.size() + 1, 0) < 0)
							std::cout << "JOIN MESSAGE IS NOT SENT TO THE MEMBERS OF THE CHANNEL\n";
					}
					// send to the client that just joined the channel the TOPIC, if there is any, then send to him the list of the members
					send_members_list(this->_ircserv, vc[1],  client_socket);
				}
			}
		}
	}
}
