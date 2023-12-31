/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:29:30 by aerrazik          #+#    #+#             */
/*   Updated: 2023/09/25 16:02:29 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"
#include "../server/ircserv.hpp"

int    ircserv::accept_client() {
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    // Accept connection from an incoming client. The accept() system call causes the process to block until a client connects to the server.
    int clientSocket = accept(_socket, (struct sockaddr*)&client, &clientSize);
    if (clientSocket == -1)
    {
        std::cerr << "Error: socket accept failed" << std::endl;
        return (-1);
    }
    if (_clients[clientSocket] == NULL) {
        add_client(clientSocket);
    }
    return (clientSocket);
}

void    ircserv::add_client(int clientSocket) {
    socklen_t len = sizeof(_addr);
    getpeername(clientSocket, (struct sockaddr*)&_addr, &len);
    std::string ip = inet_ntoa(_addr.sin_addr);

    _clients[clientSocket] = new Client();
    _clients[clientSocket]->set_hostname(ip);
    _clients[clientSocket]->set_status(OFFLINE);
}

int    ircserv::remove_client(int i, int countClients) {
    int			client_socket = fds[i].fd;
	std::string	channel;

    if (_clients[client_socket]->get_status() == HAS_QUITED) {
        // delete the client from the vector of channels
        std::map<std::string, Channel*>::iterator it = _channels.begin();
        for (; it != _channels.end(); it++) {
            std::vector<Client*>::iterator it2 = it->second->_members.begin();
            for (; it2 != it->second->_members.end(); it2++) {
                if (_clients[client_socket]->get_nickname() == (*it2)->get_nickname()) {
                    std::string msg = "\r\n:" + _clients[client_socket]->get_nickname() + "!" + _clients[client_socket]->get_username() + "@" + _clients[client_socket]->get_hostname() + " QUIT " + it->first + "\r\n";
                    forward_to_chan(*this, it->first, msg, client_socket, false);
					channel = it->first;
					if (client_in_chan(*this, channel, (*it2)->get_nickname(), 0))
						it->second->_operators_n--;
                    it->second->_members.erase(it2);
                    break ;
                }
            }
        }
        if (_clients[client_socket]) {
            delete _clients[client_socket];
            _clients.erase(client_socket);
        }
        close(fds[i].fd);
        countClients--;
        for (int j = i; j <= countClients; j++) {
            fds[j] = fds[j + 1];
        }
    }

    return (countClients);
}

