/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:06:39 by aerrazik          #+#    #+#             */
/*   Updated: 2023/09/16 11:07:51 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "ircserv.hpp"
#include "includes.hpp"

// Client class: Each client has a nickname, username and a list of channels he is in.

class Client {
    private:
        std::string _nickname;
        std::string _username;
        std::vector<std::string> _channels;
    public:
        Client();
        Client(const Client &client);
        Client &operator=(const Client &client);
        ~Client();

        std::string get_nickname() const ;
        std::string get_username() const ;
        std::vector<std::string> get_channels() const;
        void set_nickname(std::string nickname);
        void set_username(std::string username);
        void add_channel(std::string channel);
        void remove_channel(std::string channel);
};

#endif
