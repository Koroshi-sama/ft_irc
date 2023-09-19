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
// 
// void	Command::join(std::vector<std::string> &vc, int client_socket) {
// 	std::string	send_msg;
// 	if (vc.size() == 1) {
// 		std::cout << "Not enough parameters\n";
// 	}
// 	if (vc.size() > 3) {
// 		std::cout << "Too many parameters\n";
// 	}
// 	if (vc.size() == 2 || vc.size() == 3) {
// 		if (vc[1].find(',') != std::string::npos || (vc.size() == 3 && vc[2].find(',') != std::string::npos)) {
// 			std::cout << "We will ignore this req. You can't join multiple channels at the same time or issue multiple passwords\n";
// 		}
// 		else {
// 			if (this->_ircserv->_channels.find(vc[1]) == this->_ircserv->_channels.end()) {
// 				// create channel and add user       // later enable this user to be an operator
// 				this->_ircserv->_channels[vc[1]] = new Channel(vc[1]);
// 				this->_ircserv->_channels[vc[1]]->_members.push_back(this->_ircserv->_clients[client_socket]);
// 			}
// 			else {
// 				// channel exists
// 				if (this->_ircserv->_channels[vc[1]]->pass_user_limit())
// 					// send error
// 				if (this->_ircserv->_channels[vc[1]]->get_invite_bool()) {
// 					// send error
// 				}
// 				if (this->_ircserv->_channels[vc[1]]->get_key_bool()) {
// 					join_with_key(vc, client_socket);
// 				}
// 				this->_ircserv->_channels[vc[1]]->_members.push_back(this->_ircserv->_clients[client_socket]);
// 				// SUCCESS
// 				// the messages that'll be send are going to be send through the private msg function, to every member in the channel (maybe except the joiner?)
// 			}
// 		}
// 	}
// }
