/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:55:22 by aerrazik          #+#    #+#             */
/*   Updated: 2023/09/25 16:04:24 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

void Command::user(std::vector<std::string> &vc, int client_socket) {
    Client *client = _ircserv->_clients[client_socket];
    if (client) {
        if (vc.size() < 3) {
            std::string reply = std::string("461 ERR_NEEDMOREPARAMS\r\n") + "USER Not enough parameters\r\n";
            send(client_socket, reply.c_str(), reply.size(), 0);
            return;
        }
        else if (client->get_status() == ONLINE || client->get_status() == REGISTRED) {
            std::string reply = std::string("462 ERR_ALREADYREGISTRED\r\n");
            send(client_socket, reply.c_str(), reply.size(), 0);
            return;
        }
        client->set_username(vc[1]);
        client->set_hostname(vc[3]);
        client->set_realname(vc[4].substr(1));
        // Macro that means user is registred
        client->set_check_user(USERCHECKED);
        std::string reply = "001 RPL_WELCOME\r\nWelcome to the IRC Network " + client->get_nickname() + "!"+ client->get_username() + "@" + client->get_hostname() + "\r\n";
        send(client_socket, reply.c_str(), reply.size() + 1, 0);
        reply = "002 RPL_YOURHOST\r\nYour host is " + client->get_hostname() + ", running version 1.0\r\n";
        send(client_socket, reply.c_str(), reply.size() + 1, 0);
        reply = "003 RPL_CREATED\r\nThis server was created " + _ircserv->get_creation_time() + "\r\n";
        send(client_socket, reply.c_str(), reply.size() + 1, 0);
        reply = "004 RPL_MYINFO\r\nIRC 1.0 +itkol\r\n:RPL_WELCOME!" + client->get_username() + "@" + client->get_hostname() + " NICK " + client->get_nickname() + "\r\n";
        send(client_socket, reply.c_str(), reply.size() + 1, 0);
        reply = "005  RPL_ISUPPORT\r\n" + client->get_nickname() + " CHANTYPES=# CHANLIMIT=#:1\r\n";
        send(client_socket, reply.c_str(), reply.size() + 1, 0);
        client->set_status(ONLINE);
    }
}
