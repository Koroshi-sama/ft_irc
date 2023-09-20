#include "command.hpp"

// check whether the client can join the channel or not
// 		check the user limit
// 		check the key provided if the channel has a key            a key is a password set by the operator
//
// send the messages that have to be send to every member of the channel upon the successful joinment of a new member

// ---------------------------------------------------------------------------------------

// void	Command::join_with_key(std::vector<std::string> &vc, int client_socket) {
// 	if (vc.size() == 2)
// 		send(client_socket, ERR_PASSWDMISMATCH (464), sizeof(), 0);
// 	if (vc.size() == 3 && this->_ircserv->_channels[vc[1]]->get_key().strcmp(vc[2]) != 0)
// 		send(client_socket, ERR_PASSWDMISMATCH (464), sizeof(ERR_NEEDMOREPARAMS), 0);
// 
// 	if (vc.size() == 3 && this->_ircserv->_channels[vc[1]]->get_key().strcmp(vc[2]) == 0) {
// 		this->_ircserv->_channels[vc[1]]->_members.push_back(this->_ircserv->_clients[client_socket]);
// 		// SUCCESS
// 		// send message to every member in the channel
// 	}
// }

void	Command::join(std::vector<std::string> &vc, int client_socket) {
	int			target_s;
	std::string	reply;

	if (vc.size() == 1) {
		std::cout << "Not enough parameters\n";
	}
	if (vc.size() > 3) {
		std::cout << "Too many parameters\n";
	}
	if (vc.size() == 2 || vc.size() == 3) {
		if (vc[1].find(',') != std::string::npos || (vc.size() == 3 && vc[2].find(',') != std::string::npos)) {
			std::cout << "We will ignore this req. You can't join multiple channels at the same time or issue multiple passwords\n";
		}
		else {
			if (this->_ircserv->_channels.find(vc[1]) == this->_ircserv->_channels.end()) {
				// create channel and add user       // later enable this user to be an operator
				this->_ircserv->_channels[vc[1]] = new Channel(vc[1]);
				this->_ircserv->_channels[vc[1]]->_members.push_back(*this->_ircserv->_clients[client_socket]);

					reply = ":" + this->_ircserv->_clients[client_socket]->get_nickname() + " JOIN " + vc[1] + "\r\n";
					// there still 2 messages that have to be sent
					target_s = client_socket;
					if (send(target_s, reply.c_str(), reply.size() + 1, 0) < 0)
						std::cout << "JOIN MESSAGE IS NOT SENT TO THE ONLY MEMBER OF THE CHANNEL\n";
					else {std::cout << "JOIN MESSAGE IS SENT TO THE ONLY MEMBER OF THE CHANNEL\n";}
			}
			else {
				// channel exists
// 				if (this->_ircserv->_channels[vc[1]]->pass_user_limit())
// 					// send error
// 				if (this->_ircserv->_channels[vc[1]]->get_invite_bool()) {
// 					// send error
// 				}
// 				if (this->_ircserv->_channels[vc[1]]->get_key_bool()) {
// 					join_with_key(vc, client_socket);
// 				}
				this->_ircserv->_channels[vc[1]]->_members.push_back(*this->_ircserv->_clients[client_socket]);
				// SUCCESS
				for (std::vector<Client>::iterator it = this->_ircserv->_channels[vc[1]]->_members.begin();\
					it != this->_ircserv->_channels[vc[1]]->_members.end(); it++) {
					reply = ":" + this->_ircserv->_clients[client_socket]->get_nickname() + " JOIN " + vc[1] + "\r\n";
					// there still 2 messages that have to be sent
					target_s = target_socket(it->get_nickname(), this->_ircserv->_clients);
					if (send(target_s, reply.c_str(), reply.size() + 1, 0) < 0)
						std::cout << "JOIN MESSAGE IS NOT SENT TO THE MEMBERS OF THE CHANNEL\n";
				}
			}
		}
	}
}
