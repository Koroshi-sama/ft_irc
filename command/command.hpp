/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 20:06:14 by aerrazik          #+#    #+#             */
/*   Updated: 2023/09/20 09:39:55 by atouba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP

#include "../includes.hpp"
#include "../server/ircserv.hpp"

#define WELCOME 1

class ircserv;
class client;

class Command {
    public:

        Command(ircserv *ircserv);
        ~Command();
        void handle_commands(std::string command, int client_socket);
    
    private:
        ircserv *_ircserv;
        typedef void (Command::*CommandFunction)(std::vector<std::string> &, int);
        std::map<std::string, CommandFunction> _commands;
        std::map<std::string, std::vector<std::string> > _params;
		std::string	_buffer;		// Sometimes we need the whole buffer the client sent (e.g in privmsg command, the message might be "hello                               world" and it has to get sent to the target exactly like that)

        void parse_command(std::string command);

        void nick(std::vector<std::string> &vc, int client_socket);
        void pass(std::vector<std::string> &vc, int client_socket);
        void user(std::vector<std::string> &vc, int client_socket);
        void quit(std::vector<std::string> &vc, int client_socket);
        void join(std::vector<std::string> &vc, int client_socket);
//         void join_with_key(std::vector<std::string> &vc, int client_socket);
        void part(std::vector<std::string> &vc, int client_socket);
        void privmsg(std::vector<std::string> &vc, int client_socket);
        void notice(std::vector<std::string> &vc, int client_socket);
        void ping(std::vector<std::string> &vc, int client_socket);
        void pong(std::vector<std::string> &vc, int client_socket);
};


#endif
