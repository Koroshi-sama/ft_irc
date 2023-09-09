/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:28:34 by aerrazik          #+#    #+#             */
/*   Updated: 2023/09/08 10:14:09 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ircserv.hpp"

ircserv::ircserv(): _port(0), _socket(0), _password("") {}

ircserv::ircserv(int port, std::string password): _port(port), _socket(0), _password(password) {}

ircserv::ircserv(const ircserv &ircserv) {*this = ircserv;}

ircserv &ircserv::operator=(const ircserv &ircserv)
{
    if (this != &ircserv)
    {
        _port = ircserv._port;
        _socket = ircserv._socket;
        _password = ircserv._password;
    }
    return (*this);
}

ircserv::~ircserv() {}

bool    ircserv::start_server() {
    // Create socket
    std::string password = "5555";
    if (_password != password) {
        std::cerr << "Error: wrong password" << std::endl;
        return (false);
    }
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket == -1)
    {
        std::cerr << "Error: socket creation failed" << std::endl;
        return (false);
    }

    // Bind socket to port
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(_port);
    addr.sin_addr.s_addr = INADDR_ANY;

    int opt = 1;
    if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        std::cerr << "Error: setsockopt failed" << std::endl;
        close(_socket);
        return (false);
    }

    if (bind(_socket, (struct sockaddr*)&addr, sizeof(addr)) == -1) 
    {
        std::cerr << "Error: socket bind failed" << std::endl;
        // close(_socket);
        return (false);
    }

    // Mark the socket for listening in
    if (listen(_socket, MAX_NUMB_CLIENTS) == -1)
    {
        std::cerr << "Error: socket listen failed" << std::endl;
        // close(_socket);
        return (false);
    }

    std::cout << "Server started on port " << _port << std::endl;
    return (true);
}

void    ircserv::stop_server() {
    if (_socket > 0) {
        close(_socket);
    }
}
