/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:28:38 by aerrazik          #+#    #+#             */
/*   Updated: 2023/09/16 10:41:27 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSERV_HPP
#define IRCSERV_HPP

#include "client.hpp"
#include "includes.hpp"

#define MAX_HOST 1025
#define MAX_SERV 32
#define MAX_NUMB_CLIENTS 10
#define MAX_BUFFER 4096

class Client;

class ircserv
{
    public:
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
    
    private:
        int     _port;
        int     _socket;
        std::string _password;
        std::map<int, Client *> _clients;
};

#endif
