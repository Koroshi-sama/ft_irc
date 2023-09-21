/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WHOIS.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:50:26 by aerrazik          #+#    #+#             */
/*   Updated: 2023/09/20 19:47:24 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

// ":LAZYIRC 379 " + nick + " " + nick + " :is using modes +i\r\n"

void Command::whois(std::vector<std::string> &vc, int client_socket) {
    std::cout << "Whoooooois" << vc[1] << client_socket << std::endl;
    // Client *client = _ircserv->_clients[client_socket];

    // 311 RPL_WHOISUSER <nickname> <username> <hostname> * :<real name>

    // std::string reply = ":" + vc[1] +"311 RPL_WHOISUSER\r\n" + client->get_nickname() + " " + client->get_username() + " " + client->get_hostname() + " * :" + client->get_realname() + "\r\n";
    // send(client_socket, reply.c_str(), reply.size() + 1, 0);
//     std::string replay = "318 RPL_ENDOFWHOIS\r\n" + vc[1] + " :End of /WHOIS list\r\n";
//     send(client_socket, replay.c_str(), replay.size() + 1, 0);
}
