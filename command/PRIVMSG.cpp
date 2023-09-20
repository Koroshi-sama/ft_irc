#include "command.hpp"

int	target_socket(std::string nickname, std::map<int, Client*> clients) {
	std::map<int, Client*>::iterator	it;

	for (it = clients.begin(); it != clients.end(); it++) {
		if (it->second->get_nickname().compare(nickname) == 0)
			return it->first;
	}
	return -1;
}

void	target_client(int client_s, std::map<int, Client*> clients, std::string target, std::string buffer) {
	int			target_s;
	std::string	reply;
	std::string	msg;

	target_s = target_socket(target, clients);
	if (target_s > 0) {
		msg = buffer.erase(0, buffer.find(':'));
		reply = ":" + clients[client_s]->get_nickname() + " PRIVMSG " + \
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


void	target_channel(int client_s, std::map<int, Client*> clients, std::string target, std::string buffer, ircserv serv) {
	int			target_s;
	std::string	reply;
	std::string	msg;

	if (serv._channels.find(target) == serv._channels.end())
		send(client_s, "404 ERR_CANNOTSENDTOCHAN\r\n...", 32, 0);
	else {
		std::vector<Client>::iterator	it;
		for (it = serv._channels[target]->_members.begin(); it != serv._channels[target]->_members.end(); it++)
			SEND MESSAGE TO EVERY MEMBER
			
	}
// 	target_s = target_socket(target, clients);
// 	if (target_s > 0) {
// 		msg = buffer.erase(0, buffer.find(':'));
// 		reply = ":" + clients[client_s]->get_nickname() + " PRIVMSG " + \
// 				target + " " + msg + "\r\n";
// 		if (send(target_s, reply.c_str(), reply.size() + 1, 0) > 0) {
// 			std::cout << "THE MESSAGE IS SENT\n";
// 			std::cout << reply;
// 		}
// 		else
// 			std::cout << "THE MESSAGE DIDN'T GET SENT\n";
// 	}
// 	else
// 		std::cout << "TARGET NOT FOUND.................. send error later\n";
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
			target_channel();
		else
			target_client(client_socket, this->_ircserv->_clients, vc[1], _buffer);
	}
}
