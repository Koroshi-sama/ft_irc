/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 20:06:18 by aerrazik          #+#    #+#             */
/*   Updated: 2023/09/24 12:54:13 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

Command::Command(ircserv *ircserv): _ircserv(ircserv) , _bot(bot("Xbot")) {
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
                    (this->*_commands[tokens[0]])(tokens, client_socket);
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

void Command::part(std::vector<std::string> &vc, int client_socket) {
    std::cout << "Paaaaaart" << vc[1] << client_socket << std::endl;
}

void Command::notice(std::vector<std::string> &vc, int client_socket) {
    std::cout << "Nooooooootice" << vc[1] << client_socket << std::endl;
}

void Command::ping(std::vector<std::string> &vc, int client_socket) {
    std::cout << "Piiiiiiiiing" << vc[1] << client_socket << std::endl;
    // Client *client = _ircserv->_clients[client_socket];
    std::string reply = "\r\nPONG :" + vc[1] + "\r\n";
    send(client_socket, reply.c_str(), reply.size(), 0);
}

void Command::pong(std::vector<std::string> &vc, int client_socket) {
    std::cout << "Pooooooong" << vc[1] << client_socket << std::endl;
}
