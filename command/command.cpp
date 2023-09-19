/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 20:06:18 by aerrazik          #+#    #+#             */
/*   Updated: 2023/09/19 10:31:51 by aerrazik         ###   ########.fr       */
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
}

Command::~Command() {}

void Command::handle_commands(std::string command, int client_socket) {
    parse_command(command);
    std::map<std::string, std::vector<std::string> >::iterator it = _params.begin();
    for (; it != _params.end(); it++) {
        if (_commands.find(it->first) != _commands.end()) {
            (this->*_commands[it->first])(it->second, client_socket);
        }
    }
}

void Command::parse_command(std::string command) {
    command = strtrim(command);
    std::vector<std::string> provisory = split(command, '\n');
    std::vector<std::string>::iterator it = provisory.begin();
    for (; it != provisory.end(); it++) {
        std::string temp = strtrim(*it);
        std::vector<std::string> tokens = split(temp, ' ');
        if (!tokens.empty()) {
            _params[tokens[0]] = tokens;
        }
    }
}

void Command::pass(std::vector<std::string> &vc, int client_socket) {
    std::cout << "Paaaaaass" << vc[1] << client_socket << std::endl;
}

void Command::quit(std::vector<std::string> &vc, int client_socket) {
    std::cout << "Quuuuuuit" << vc[1] << client_socket << std::endl;
}

void Command::join(std::vector<std::string> &vc, int client_socket) {
    std::cout << "Joooooooin" << vc[1] << client_socket << std::endl;
}

void Command::part(std::vector<std::string> &vc, int client_socket) {
    std::cout << "Paaaaaart" << vc[1] << client_socket << std::endl;
}

void Command::privmsg(std::vector<std::string> &vc, int client_socket) {
    std::cout << "Prrrrrrrivmsg" << vc[1] << client_socket << std::endl;
}

void Command::notice(std::vector<std::string> &vc, int client_socket) {
    std::cout << "Nooooooootice" << vc[1] << client_socket << std::endl;
}

void Command::ping(std::vector<std::string> &vc, int client_socket) {
    std::cout << "Piiiiiiiiing" << vc[1] << client_socket << std::endl;
}

void Command::pong(std::vector<std::string> &vc, int client_socket) {
    std::cout << "Pooooooong" << vc[1] << client_socket << std::endl;
}


