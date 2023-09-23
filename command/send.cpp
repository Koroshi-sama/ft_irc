#include "command.hpp"

// There are two types of messages:
// 		Command messages:   (serv, client_s, command, param) sends to client_s
//	   	"\r\n:" + client_s.get_nickname() + " " + command + " " + param + "\r\n"
//		CRLN :<client> <command> <param> CRLN
// 
// 		Numerical messages: (serv, client_s, num, param) sends to client_s
//		"\r\n:" + client_s.ghostsname() + num + clientNickname + param + "\r\n"
//		CRLN :<hostname> <num> <client> <param> CRLN

void	command_message(ircserv& serv, int client_s, std::string command,
						std::string param) {
// 	std::string	msg = "\r\n:" + serv._clients[client_s]->get_nickname() + 
// 						" " + command + " " + param + "\r\n";
	std::string	msg = "\r\n:" + serv._clients[client_s]->get_nickname() + \
						"!" + serv._clients[client_s]->get_username() + \
						"@localhost " + command + " " + param + "\r\n";
	std::cout << "command_message: {" << msg << "}" << std::endl;

	if (send(client_s, msg.c_str(), msg.size() + 1, 0) < 0)
		std::cout << "command " + command + " message didn't get sent\n";
}

void	numerical_message(ircserv& serv, int client_s, int num,
							std::string param) {
	std::string	num_s = to_string(num);
// 	std::string	msg = "\r\n:" + serv._clients[client_s]->get_hostname
// + " " + command + " " + param + "\r\n";
	std::string	msg = "\r\n:localhost " + num_s + " " + \
					serv._clients[client_s]->get_nickname() + " " + \
					param + "\r\n";

	std::cout << "numerical_message: {" << msg << "}" << std::endl;

	if (send(client_s, msg.c_str(), msg.size() + 1, 0) < 0)
		std::cout << "numeric " + num_s + " message didn't get sent\n";
}
