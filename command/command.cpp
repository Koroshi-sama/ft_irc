/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 20:06:18 by aerrazik          #+#    #+#             */
/*   Updated: 2023/09/21 13:42:27 by atouba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

Command::Command(ircserv *ircserv): _ircserv(ircserv) {
    _commands["PASS"] = &Command::pass;
    _commands["NICK"] = &Command::nick;
    _commands["USER"] = &Command::user;
    _commands["QUIT"] = &Command::quit;
    _commands["JOIN"] = &Command::join;
    _commands["PART"] = &Command::part;
    _commands["PRIVMSG"] = &Command::privmsg;
    _commands["NOTICE"] = &Command::notice;
    _commands["PING"] = &Command::ping;
    _commands["PONG"] = &Command::pong;
    _commands["WHOIS"] = &Command::whois;
    _commands["MODE"] = &Command::mode;
}

Command::~Command() {}

void Command::handle_commands(std::string command, int client_socket) {
	_buffer = command;
    parse_command(command);
    std::map<std::string, std::vector<std::string> >::iterator it = _params.begin();
    for (; it != _params.end(); it++) {
        if (_commands.find(it->first) != _commands.end()) {
            (this->*_commands[it->first])(it->second, client_socket);
        }
    }
    // clean _params map
    _params.clear();
}

void Command::parse_command(std::string command) {
    command = strtrim(command);
    std::vector<std::string> provisory = split(command, '\n');
    std::vector<std::string>::iterator it = provisory.begin();
    for (; it != provisory.end(); it++) {
        std::string temp = strtrim(*it);
        std::vector<std::string> tokens = split(temp, ' ');
        if (!tokens.empty()) {
            for (std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); it++) {
                *it = strtrim(*it);
            }
            _params[tokens[0]] = tokens;
        }
    }
}

void Command::pass(std::vector<std::string> &vc, int client_socket) {
    std::cout << "Paaaaaass" << vc[1] << client_socket << std::endl;
}

void Command::quit(std::vector<std::string> &vc, int client_socket) {
    std::cout << "Quuuuuuit" << vc[1] << client_socket << std::endl;
    // It should delete the client that has quit the client and send a message to all the clients in the same channel
    Client *client = _ircserv->_clients[client_socket];
    std::string reply = "ERROR :Closing Link: " + client->get_nickname() + " (" + vc[1] + ")\r\n";
    send(client_socket, reply.c_str(), reply.size(), 0);
    close(client_socket);
    _ircserv->_clients.erase(client_socket);

}

void Command::part(std::vector<std::string> &vc, int client_socket) {
    std::cout << "Paaaaaart" << vc[1] << client_socket << std::endl;
}

void Command::notice(std::vector<std::string> &vc, int client_socket) {
    std::cout << "Nooooooootice" << vc[1] << client_socket << std::endl;
}

void Command::ping(std::vector<std::string> &vc, int client_socket) {
    std::cout << "Piiiiiiiiing" << vc[1] << client_socket << std::endl;
    // Client *client = _ircserv->_clients[client_socket];
    std::string reply = "\r\nPONG 127.0.0.1 :127.0.0.1\r\n";
    send(client_socket, reply.c_str(), reply.size(), 0);
}

void Command::pong(std::vector<std::string> &vc, int client_socket) {
    std::cout << "Pooooooong" << vc[1] << client_socket << std::endl;
}
