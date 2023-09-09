/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:06:39 by aerrazik          #+#    #+#             */
/*   Updated: 2023/09/08 17:05:21 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "ircserv.hpp"
#include "includes.hpp"


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
