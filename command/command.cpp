/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 20:06:18 by aerrazik          #+#    #+#             */
/*   Updated: 2023/09/25 12:53:04 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

Command::Command(ircserv *ircserv): _ircserv(ircserv) {
    _commands["PASS"] = &Command::pass;
    _commands["NICK"] = &Command::nick;
    _commands["USER"] = &Command::user;
    _commands["QUIT"] = &Command::quit;
    _commands["JOIN"] = &Command::join;
    _commands["PRIVMSG"] = &Command::privmsg;
    _commands["PING"] = &Command::ping;
    _commands["MODE"] = &Command::mode;
    _commands["KICK"] = &Command::kick;
    _commands["INVITE"] = &Command::invite;
    _commands["MODE"] = &Command::mode;
    _commands["TOPIC"] = &Command::topic;
}

Command::~Command() {}

void Command::handle_commands(std::string command, int client_socket) {
	_buffer = command;
    parse_command(command, client_socket);
}

void Command::parse_command(std::string command, int client_socket) {
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
            std::cout << "Command in the parsing funtcion: " << tokens[0] << std::endl;
            if (_commands.find(tokens[0]) != _commands.end()) {
                if (tokens[0] == "PASS" || _ircserv->_clients[client_socket]->get_check_pass() == PASSWORD) {
                    if (tokens[0] == "PASS" || tokens[0] == "NICK" || tokens[0] == "USER" 
                        || (_ircserv->_clients[client_socket]->get_check_nick() == NICKCHECKED 
                        && _ircserv->_clients[client_socket]->get_check_user() == USERCHECKED)) {
                        (this->*_commands[tokens[0]])(tokens, client_socket);
                    }
                    // (this->*_commands[tokens[0]])(tokens, client_socket);
                }
            }
        }
    }
    _params.clear();
}

void Command::quit(std::vector<std::string> &vc, int client_socket) {
    std::cout << "Quuuuuuit" << client_socket << std::endl;
    // It should delete the client that has quit the client and send a message to all the clients in the same channel
    Client *client = _ircserv->_clients[client_socket];
    std::string second_vs = "";
    if (vc.size() > 1) {
        second_vs = vc[1];
    }
    std::string reply = "ERROR :Closing Link: " + client->get_nickname() + " (" + second_vs + ")\r\n";
    send(client_socket, reply.c_str(), reply.size(), 0);
    client->set_status(HAS_QUITED);
}

void Command::ping(std::vector<std::string> &vc, int client_socket) {
    std::cout << "Piiiiiiiiing" << vc[1] << client_socket << std::endl;
    // Client *client = _ircserv->_clients[client_socket];
    std::string reply = "\r\nPONG :" + vc[1] + "\r\n";
    send(client_socket, reply.c_str(), reply.size(), 0);
}

