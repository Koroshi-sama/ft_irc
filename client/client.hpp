/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:06:39 by aerrazik          #+#    #+#             */
/*   Updated: 2023/09/18 18:47:44 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../server/ircserv.hpp"
#include "../replays.hpp"
#include "../includes.hpp"

#define ONLINE 2
#define REGISTRED 1
#define OFFLINE 0

// Client class: Each client has a nickname, username and a list of channels he is in.

class Client {
    private:
        std::string _nickname;
        std::string _username;
        std::string _realname;
        std::string _hostname;
        int         _status;
        std::vector<std::string> _channels;

    public:
        Client();
        Client(const Client &client);
        Client &operator=(const Client &client);
        ~Client();

        std::string get_nickname() const ;
        std::string get_username() const ;
        std::string get_realname() const ;
        std::string get_hostname() const ;
        int         get_status() const ;
        std::vector<std::string> get_channels() const;
        void set_nickname(std::string nickname);
        void set_username(std::string username);
        void set_realname(std::string realname);
        void set_hostname(std::string hostname);
        void set_status(int status);
        void add_channel(std::string channel);
        void remove_channel(std::string channel);
};

#endif
