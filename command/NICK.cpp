/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:49:04 by aerrazik          #+#    #+#             */
/*   Updated: 2023/09/25 12:28:18 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

bool valid_nickname(std::string nickname) {
    std::string::iterator it = nickname.begin();
    for (; it != nickname.end(); it++) {
        if (!((*it >= '0' && *it <= '9') || (*it >= 'A' && *it <= '}'))) {
            return (false);
        }
    }
    return (true);
}

bool Command::check_nickname(std::string nickname) {
    std::map<int, Client *>::iterator it = _ircserv->_clients.begin();
    for (; it != _ircserv->_clients.end(); it++) {
        if (it->second->get_nickname() == nickname) {
            return (false);
        }
    }
    return (true);
}

void Command::nick(std::vector<std::string> &vc, int client_socket) {
    Client *client = _ircserv->_clients[client_socket];
    if (vc.size() < 2) {
        std::string reply = std::string("431 ERR_NONICKNAMEGIVEN\r\n") + "No nickname given\r\n";
        send(client_socket, reply.c_str(), reply.size(), 0);
    }
    else if (!valid_nickname(vc[1])) {
        std::string reply = std::string("432 ERR_ERRONEUSNICKNAME\r\n") + vc[1] + "Erroneus nickname\r\n";
        send(client_socket, reply.c_str(), reply.size(), 0);
    }
    else if (!check_nickname(vc[1])) {
        if (client->get_nickname() == "") {
            std::string nickname = vc[1] + "_";
            while (!check_nickname(nickname)) {
                nickname += "_";
            }
            client->set_nickname(nickname);
            // macro that means user is registred
            client->set_check_nick(NICKCHECKED);
            std::cout << "Nickname changed to " << client->get_nickname() << std::endl;
        } else {
            std::cout << "Nickname already exists" << std::endl;
            // std::string reply = "433 ERR_NICKNAMEINUSE\r\n";
            // send(client_socket, reply.c_str(), reply.size(), 0);
            numerical_message(*_ircserv, client_socket, 433, vc[1] + " :Nickname is already in use");
        }
        // add an underscore to the nickname and then check if it exists if no set it as the new nickname if yes add an other underscore and so on
    }
    else
    {
        if (client->get_nickname() == "") {
            client->set_nickname(vc[1]);
            // macro that means user is registred
            client->set_check_nick(NICKCHECKED);
        } else {
            //change nickname and send a reply to the concerned client
            std::string old_nickname = client->get_nickname();
            client->set_nickname(vc[1]);
            std::cout << "Old --> " << old_nickname << "New--> " << vc[1] << std::endl;
            // :hhhh!aerrazik@localhost NICK hit
            std::string reply = "\r\n:" + old_nickname + "!" + client->get_username() + "@" + client->get_hostname() + " NICK " + vc[1] + "\r\n";
            send(client_socket, reply.c_str(), reply.size(), 0);
            std::cout << "Channel : " << client->get_channel() << std::endl;
            if (client->get_channel() != "") {
                forward_to_chan(*_ircserv, client->get_channel(), reply, client_socket, false);
            }
        }
    }
}
