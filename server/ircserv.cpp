/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:28:34 by aerrazik          #+#    #+#             */
/*   Updated: 2023/09/19 09:19:08 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ircserv.hpp"

ircserv::ircserv(): _port(0), _socket(0), _addr(), _password("") {}

ircserv::ircserv(int port, std::string password): _port(port), _socket(0), _password(password) {}

ircserv::ircserv(const ircserv &ircserv) {*this = ircserv;}

ircserv &ircserv::operator=(const ircserv &ircserv)
{
    if (this != &ircserv)
    {
        _port = ircserv._port;
        _socket = ircserv._socket;
        _addr   = ircserv._addr;
        _password = ircserv._password;
    }
    return (*this);
}

ircserv::~ircserv() {}

int     ircserv::get_socket() const {
    return (_socket);
}

int     ircserv::get_port() const {
    return (_port);
}

std::string ircserv::get_creation_time() const {
    return (creation_time);
}

bool    ircserv::start_server() {
    // Create socket with the socket() system call. AF_INET (IPV4) is the address domain of the socket, SOCK_STREAM is the type of socket, 0 is the protocol.
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

    // Bind socket to port with the bind() system call.

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(_port);
    addr.sin_addr.s_addr = INADDR_ANY;

    int opt = 1;
    // Setsockopt() is used to allow the local address to be reused when the server is restarted before the required wait time expires.
    if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        std::cerr << "Error: setsockopt failed" << std::endl;
        close(_socket);
        return (false);
    }

    if (bind(_socket, (struct sockaddr*)&addr, sizeof(addr)) == -1) 
    {
        std::cerr << "Error: socket bind failed" << std::endl;
        return (false);
    }

    // Mark the socket for listening in
    if (listen(_socket, MAX_NUMB_CLIENTS) == -1)
    {
        std::cerr << "Error: socket listen failed" << std::endl;
        return (false);
    }
    
    _addr = addr;
    // store the time when the server started and be in this form  11:58:05 Sep 16 2023 
    time_t now = time(0);
    creation_time = ctime(&now);
    std::cout << creation_time << std::endl;
    std::cout << "Server started on port " << _port << std::endl;
    return (true);
}

void    ircserv::stop_server() {
    if (_socket > 0) {
        close(_socket);
    }
}
