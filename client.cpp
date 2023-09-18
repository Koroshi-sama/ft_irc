/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:29:30 by aerrazik          #+#    #+#             */
/*   Updated: 2023/09/18 10:23:06 by atouba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

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
    std::cout << "Client " << clientSocket << " connected" << std::endl;
    return (clientSocket);
}

void    ircserv::add_client(int clientSocket) {
    std::string welcome_name = "Welcome to the server!\nPlease enter your nickname \nand username using this commands:\nNICK <nickname>\nUSER <username>\n";
    std::string welcome = GREEN + welcome_name + RESET;
    // Send welcome message to the connected client. The send() system call is similar to write() but it is used for sockets instead of file descriptors.
    send(clientSocket, welcome.c_str(), welcome.size() + 1, 0);
    _clients[clientSocket] = new Client();
}

void    ircserv::broadcast_message(int sender, std::string message) {
    if (_clients[sender]) {
        std::cout << "Client " << sender << " sent: " << message << std::endl;
        std::vector<std::string> tokens = split(message, ' ');
        std::cout << tokens[0] << std::endl;
        if (tokens[0] == "NICK") {
            _clients[sender]->set_nickname(set_color(tokens[1]));
        }
        else if (tokens[0] == "USER") {
            _clients[sender]->set_username(set_color(tokens[1]));
        }
        else if (tokens[0] == "JOIN") {
            _clients[sender]->add_channel(set_color(tokens[1]));
        }
        else if (tokens[0] == "PART") {
            _clients[sender]->remove_channel(set_color(tokens[1]));
        }
        // else if (tokens[0] == "PRIVMSG") {
        //     std::string channel = tokens[1];
        //     std::string msg = tokens[2];
        //     for (std::vector<int>::size_type i = 0; i < _connected_clients.size(); i++) {
        //         if (_clients[_connected_clients[i]]->get_channels().size() > 0) {
        //             std::vector<std::string> channels = _clients[_connected_clients[i]]->get_channels();
        //             for (std::vector<std::string>::size_type j = 0; j < channels.size(); j++) {
        //                 if (channels[j] == channel) {
        //                     send(_connected_clients[i], msg.c_str(), msg.size() + 1, 0);
        //                 }
        //             }
        //         }
        //     }
        // }
        else {
            // Send message to all clients except the sender. Checks if the sender has a nickname, if not, send the sender's socket number.
            for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); it++) {
                if (it->first != sender) {
                    if (_clients[sender]->get_nickname() != "") {
                        message = _clients[sender]->get_nickname() +": " + message;
                    } else {
                        message = to_string(sender) + ": " + message;
                    }
                    send(it->first, message.c_str(), message.size() + 1, 0);
                }
            }
        }
    }
}

void    ircserv::remove_client(int client_socket) {
    if (_clients[client_socket]) {
        delete _clients[client_socket];
        _clients.erase(client_socket);
    }
}

