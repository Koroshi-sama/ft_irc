/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:17:34 by aerrazik          #+#    #+#             */
/*   Updated: 2023/09/25 08:35:45 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

void Command::pass(std::vector<std::string> &vc, int client_socket) {
    std::string password = _ircserv->get_password();
    std::cout << "Paaaaaass" << client_socket << std::endl;
    std::string second_vc = "";
    if (vc.size() > 1) {
        second_vc = vc[1];
    }
    if (vc.size() < 2) {
        std::string reply = std::string("461 ERR_NEEDMOREPARAMS\r\n") + "PASS :Not enough parameters\r\n";
        send(client_socket, reply.c_str(), reply.size(), 0);
        // _ircserv->remove_client(client_socket, _ircserv->countClients);
    }
    else if (second_vc != password) {
        std::string reply = std::string("464 ERR_PASSWDMISMATCH\r\n") + "Password incorrect\r\n";
        send(client_socket, reply.c_str(), reply.size(), 0);
        // _ircserv->remove_client(client_socket, _ircserv->countClients);
    }
    else if (_ircserv->_clients[client_socket]->get_check_pass() == PASSWORD) {
        std::string reply = std::string("462 ERR_ALREADYREGISTRED\r\n") + "Unauthorized command (already registered)\r\n";
        send(client_socket, reply.c_str(), reply.size(), 0);
    }
    else if (second_vc == password) {
        _ircserv->_clients[client_socket]->set_check_pass(PASSWORD);
    }
}
