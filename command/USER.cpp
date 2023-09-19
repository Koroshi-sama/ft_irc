/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:55:22 by aerrazik          #+#    #+#             */
/*   Updated: 2023/09/19 10:19:01 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

void Command::user(std::vector<std::string> &vc, int client_socket) {
    Client *client = _ircserv->_clients[client_socket];
    if (client) {
        if (vc.size() < 3) {
            std::string reply = std::string("461 ERR_NEEDMOREPARAMS\r\n") + "USER Not enough parameters";
            send(client_socket, reply.c_str(), reply.size() + 1, 0);
            return;
        }
        else if (client->get_status() == ONLINE || client->get_status() == REGISTRED) {
            std::string reply = std::string("462 ERR_ALREADYREGISTRED\r\n");
            send(client_socket, reply.c_str(), reply.size() + 1, 0);
            return;
        }
        client->set_username(vc[1]);
        client->set_realname(vc[4].substr(1));
        std::cout << client->get_nickname();
        std::string reply = "001 RPL_WELCOME\r\nWelcome to the IRC Network " + client->get_nickname() + "!"+ client->get_username() + "@" + client->get_hostname() + "\r\n";
        send(client_socket, reply.c_str(), reply.size() + 1, 0);
        reply = "002 RPL_YOURHOST\r\nYour host is " + client->get_hostname() + ", running version 1.0\r\n";
        send(client_socket, reply.c_str(), reply.size() + 1, 0);
        reply = "003 RPL_CREATED\r\nThis server was created " + _ircserv->get_creation_time() + "\r\n";
        send(client_socket, reply.c_str(), reply.size() + 1, 0);
        reply = "004 RPL_MYINFO\r\nIRC 1.0 test test\r\n";
        send(client_socket, reply.c_str(), reply.size() + 1, 0);
        std::cout << "Wach tsifet" << std::endl;
        reply = "005 RPL_BOUNCE\r\nTry server IRC, port 6670";
        send(client_socket, reply.c_str(), reply.size() + 1, 0);
        client->set_status(ONLINE);
    }
}
