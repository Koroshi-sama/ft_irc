#include "command.hpp"

int	target_socket(std::string nickname, std::map<int, Client*> clients) {
	std::map<int, Client*>::iterator	it;

	for (it = clients.begin(); it != clients.end(); it++) {
		if (it->second->get_nickname().compare(nickname) == 0)
			return it->first;
	}
	return -1;
}

void Command::privmsg(std::vector<std::string> &vc, int client_socket) {
	int	target_s;
	char msg[64] = "this message is sent from a client to you";

	if (vc.size() < 3)
		std::cout << "LESS THAN 3 MESSAGES.................. send error (if any) later\n";
	else if (this->_ircserv->_clients.find(client_socket) == this->_ircserv->_clients.end())  // remove this condition later
		std::cout << "WTF, CLIENT SOCKET NOT FOUND\n";
	else {
		target_s = target_socket(vc[1], this->_ircserv->_clients);
		if (target_s > 0)
			send(target_s, msg, sizeof(msg), 0);
		else
			std::cout << "TARGET NOT FOUND.................. send error later\n";
	}
}
