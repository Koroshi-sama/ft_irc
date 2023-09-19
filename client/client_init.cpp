/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_init.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 22:36:24 by aerrazik          #+#    #+#             */
/*   Updated: 2023/09/18 18:47:31 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

Client::Client(): _nickname(""), _username(""), _realname(""), _status(0) {}

Client::Client(const Client &client) {*this = client;}

Client &Client::operator=(const Client &client)
{
    if (this != &client)
    {
        _nickname = client._nickname;
        _username = client._username;
    }
    return (*this);
}

void    Client::set_nickname(std::string nickname) {
    _nickname = nickname;
}

void    Client::set_username(std::string username) {
    _username = username;
}

void    Client::set_realname(std::string realname) {
    _realname = realname;
}

void    Client::set_hostname(std::string hostname) {
    _hostname = hostname;
}

void    Client::set_status(int status) {
    _status = status;
}

std ::string    Client::get_nickname() const {
    return (_nickname);
}

std ::string    Client::get_username() const {
    return (_username);
}

std ::string    Client::get_realname() const {
    return (_realname);
}

std ::string    Client::get_hostname() const {
    return (_hostname);
}

int    Client::get_status() const {
    return (_status);
}

Client::~Client() {}

std::vector<std::string> Client::get_channels() const {
    return (_channels);
}

void    Client::add_channel(std::string channel) {
    _channels.push_back(channel);
}

void    Client::remove_channel(std::string channel) {
    for (std::vector<std::string>::size_type i = 0; i < _channels.size(); i++) {
        if (_channels[i] == channel) {
            _channels.erase(_channels.begin() + i);
            break;
        }
    }
}

