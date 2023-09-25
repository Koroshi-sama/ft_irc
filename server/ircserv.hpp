/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:28:38 by aerrazik          #+#    #+#             */
/*   Updated: 2023/09/25 08:32:46 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSERV_HPP
#define IRCSERV_HPP

#include "../includes.hpp"
#include "../channel/Channel.hpp"

#define MAX_HOST 1025
#define MAX_SERV 32
#define MAX_NUMB_CLIENTS 1024
#define MAX_BUFFER 4096

class Client;

class ircserv
{
    public:
        std::map<int, Client *>			_clients;
		std::map<std::string, Channel*>	_channels;
        ircserv();
        ircserv(int port, std::string password);
        ircserv(const ircserv &ircserv);
        ircserv &operator=(const ircserv &ircserv);
        ~ircserv();

        void    set_password(std::string pass);
        bool    start_server();
        int     accept_client();
        void    stop_server();
        void    add_client(int client_socket);
        int    remove_client(int i, int countClients);
        int     get_socket() const ;
        int     get_port() const ;
        std::string get_password();
        std::string get_creation_time() const;

        struct pollfd fds[MAX_NUMB_CLIENTS];
        int countClients;
    
    private:
        int     _port;
        int     _socket;
        struct sockaddr_in _addr;
        std::string _password;
        std::string creation_time;
};

void	forward_to_chan(ircserv& serv, std::string chan, std::string msg, int client_s, bool requester_included);

#endif
