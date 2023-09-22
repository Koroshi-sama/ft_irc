#include "command.hpp"

int	target_socket(std::string nickname, std::map<int, Client*>& clients) {
	std::map<int, Client*>::iterator	it;

	for (it = clients.begin(); it != clients.end(); it++) {
		if (it->second->get_nickname().compare(nickname) == 0)
			return it->first;
	}
	return -1;
}

void	target_client(int client_s, std::map<int, Client*>& clients, std::string target, std::string buffer) {
	int			target_s;
	std::string	reply;
	std::string	msg;

	target_s = target_socket(target, clients);
	if (target_s > 0) {
		msg = buffer.erase(0, buffer.find(':'));
		reply = "\r\n:" + clients[client_s]->get_nickname() + " PRIVMSG " + \
				target + " " + msg + "\r\n";
		if (send(target_s, reply.c_str(), reply.size() + 1, 0) > 0) {
			std::cout << "THE MESSAGE IS SENT\n";
			std::cout << reply;
		}
		else
			std::cout << "THE MESSAGE DIDN'T GET SENT\n";
	}
	else
		std::cout << "TARGET NOT FOUND.................. send error later\n";
}

// give a msg, it will simply forward it to all the members of the channel, except the sender
void	forward_to_chan(ircserv& serv, std::string chan, std::string msg, int client_s, bool requester_included) {
	std::vector<Client>::iterator	it;
	int								target_s;

	for (it = serv._channels[chan]->_members.begin(); it != serv._channels[chan]->_members.end(); it++) {
		if (!requester_included && target_socket(it->get_nickname(), serv._clients) == client_s)
			continue ;
		target_s = target_socket(it->get_nickname(), serv._clients);
		if (send(target_s, msg.c_str(), msg.size() + 1, 0) < 0)
			std::cout << "THE MESSAGE IS NOT SENT TO A MEMBER IN THE CHANNEL\n";
	}
}

// later check the other conditions (if any) before sending a message to a channel
void	target_channel(int client_s, std::map<int, Client*> clients, std::string target, std::string buffer, ircserv& serv) {
// 	int			target_s;
	std::string	reply;
	std::string	msg;

	if (serv._channels.find(target) == serv._channels.end()) {
		std::cout << "CHANNel not found\n";
		send(client_s, "403 ERR_NOSUCHCHANNEL\r\n...", 27, 0);
	}
	else {
		msg = buffer.erase(0, buffer.find(':'));
		reply = "\r\n:" + clients[client_s]->get_nickname() + " PRIVMSG " + \
				target + " " + msg + "\r\n";
		forward_to_chan(serv, target, reply, client_s, false);
	}
}


void Command::privmsg(std::vector<std::string> &vc, int client_socket) {
	std::string	msg;
	std::string	reply;

	if (vc.size() < 3)
		std::cout << "LESS THAN 3 ARGS.................. send error (if any) later\n";
	else if (this->_ircserv->_clients.find(client_socket) == this->_ircserv->_clients.end())  // remove this condition later
		std::cout << "WTF, CLIENT SOCKET NOT FOUND\n";
	else {
		if (vc[1][0] == '#')
			target_channel(client_socket, this->_ircserv->_clients, vc[1], _buffer, *this->_ircserv);
		else
			target_client(client_socket, this->_ircserv->_clients, vc[1], _buffer);
	}
}
