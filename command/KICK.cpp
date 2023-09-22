#include "command.hpp"

std::string	socket_nickname(ircserv& serv, int client_s) {
	std::string		client_nick = serv._clients[client_s]->get_nickname();

	return client_nick;
}

// checks whether or not the user client_nick is in channel, if range == 0 it checks
// if user is operator in the channel, otherwise it checks if he exist in the channel
bool	client_in_chan(ircserv& serv, std::string& chan, std::string client_nick, int range) {
	unsigned int	op_n = serv._channels[chan]->_members.size();

	if (range == 0)
		op_n = serv._channels[chan]->_operators_n;
	for (unsigned int i = 0; i < op_n; i++) {
		if (serv._channels[chan]->_members[i].get_nickname().compare(client_nick) == 0)
			return true;
	}
	return false;
}

// chan argument (channel) can be given as a command also, when errors have <command> in place of <channel>
void	send_error(int error, std::string client_nick, int client_s, std::string chan, std::string msg) {
	// localhost should be replaced by hostname
	std::string	error_msg =  "\r\n:localhost " + to_string(error) + " " + client_nick + " " + \
						chan + " :" + msg + "\r\n";
	
	if (send(client_s, error_msg.c_str(), error_msg.size() + 1, 0) < 0)
		std::cout << "ERROR NOT SEND TO USER WHO'S NOT OP\n";
	else
		std::cout << "ERROR SENT\n" << error_msg << std::endl;
}

// check channel exists
// check requester is operator in channel
// check target is in channel
bool	check_kick_req(std::vector<std::string>& vc, int client_s, ircserv& serv) {
	std::string	client_nick = socket_nickname(serv, client_s);

	if (vc.size() < 3)
		return (send_error(461, client_nick, client_s, vc[1], "Not enough parameters"), false);    // maybe this error is sent by default by irssi
	if (serv._channels.find(vc[1]) == serv._channels.end())
		return (send_error(401, client_nick, client_s, vc[1], "No such nick/channel"), false);
	// maybe should also check if client is not in channel
	if (!client_in_chan(serv, vc[1], client_nick, 0))
		return (send_error(482, client_nick, client_s, vc[1], " You're not a channel operator"), false);
	if (!client_in_chan(serv, vc[1], vc[2], -1))
		return (send_error(401, client_nick, client_s, vc[1], "No such nick/channel"), false);
	return true;
}

void	remove_user(ircserv& serv, std::string chan, std::string user) {
	std::vector<Client>::iterator	it = serv._channels[chan]->_members.begin();

	for (; it != serv._channels[chan]->_members.end(); it++) {
		if (it->get_nickname().compare(user) == 0) {
			serv._channels[chan]->_members.erase(it);
			return ;
		}
	}
}

// ! should send the corresponding errors
void	Command::kick(std::vector<std::string> &vc, int client_socket) {
	std::string	reply;

	if (!check_kick_req(vc, client_socket, *_ircserv)) {
		std::cout << "error in kick request\n";
		return ;
	}
	reply = "\r\n:" + socket_nickname(*_ircserv, client_socket) + " KICK " + vc[1] \
		+ " " + vc[2] + " "  + _ircserv->_channels[vc[1]]->_default_kick_msg + "\r\n";
	forward_to_chan(*_ircserv, vc[1], reply, client_socket, true);
	remove_user(*_ircserv, vc[1], vc[2]);
}
