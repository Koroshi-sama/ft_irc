/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 18:30:13 by aerrazik          #+#    #+#             */
/*   Updated: 2023/09/19 19:05:28 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

void Command::mode(std::vector<std::string> &vc, int client_socket) {
    std::cout << "Mooooooode" << vc[1] << client_socket << std::endl;
    // Client *client = _ircserv->_clients[client_socket];
    
    std::string replay = "221 RPL_UMODEIS\r\n";
    send(client_socket, replay.c_str(), replay.size() + 1, 0);
}