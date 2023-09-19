/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:28:38 by aerrazik          #+#    #+#             */
/*   Updated: 2023/09/19 19:14:33 by atouba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSERV_HPP
#define IRCSERV_HPP

#include "../includes.hpp"
#include "../channel/Channel.hpp"

#define MAX_HOST 1025
#define MAX_SERV 32
#define MAX_NUMB_CLIENTS 10
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

        bool    start_server();
        int     accept_client();
        void    stop_server();
        void    add_client(int client_socket);
        void    broadcast_message(int sender, std::string message);
        void    remove_client(int client_socket);
        int     get_socket() const ;
        int     get_port() const ;
        std::string get_creation_time() const;
        void    sendNumericReply(int clientSocket, std::string replay);
    
    private:
        int     _port;
        int     _socket;
        struct sockaddr_in _addr;
        std::string _password;
        std::string creation_time;
};

#endif
