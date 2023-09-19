/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:49:04 by aerrazik          #+#    #+#             */
/*   Updated: 2023/09/19 10:32:57 by aerrazik         ###   ########.fr       */
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

void Command::nick(std::vector<std::string> &vc, int client_socket) {
    
    if (vc[1].empty() && _ircserv->_clients[client_socket]->get_nickname().empty()) {
        std::string reply = std::string("431 ERR_NONICKNAMEGIVEN\r\n") + "No nickname given";
        send(client_socket, reply.c_str(), reply.size() + 1, 0);
    }
    else if (!valid_nickname(vc[1])) {
        std::string reply = std::string("432 ERR_ERRONEUSNICKNAME\r\n") + vc[1] + "Erroneus nickname";
        send(client_socket, reply.c_str(), reply.size() + 1, 0);
    }
    else
    {
        Client *client = _ircserv->_clients[client_socket];
        if (client->get_status() == ONLINE || client->get_status() == REGISTRED) {
            std::string reply = std::string("433 ERR_NICKNAMEINUSE\r\n") + vc[1] + "Nick" + client->get_nickname() + "is already in use";
            send(client_socket, reply.c_str(), reply.size() + 1, 0);
        }
        else {
            client->set_nickname(vc[1]);
        }

    } 
}

