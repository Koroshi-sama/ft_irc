/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 20:06:14 by aerrazik          #+#    #+#             */
/*   Updated: 2023/09/19 10:30:51 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP

#include "../includes.hpp"
#include "../client/client.hpp"
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

        void parse_command(std::string command);

        void nick(std::vector<std::string> &vc, int client_socket);
        void pass(std::vector<std::string> &vc, int client_socket);
        void user(std::vector<std::string> &vc, int client_socket);
        void quit(std::vector<std::string> &vc, int client_socket);
        void join(std::vector<std::string> &vc, int client_socket);
        void part(std::vector<std::string> &vc, int client_socket);
        void privmsg(std::vector<std::string> &vc, int client_socket);
        void notice(std::vector<std::string> &vc, int client_socket);
        void ping(std::vector<std::string> &vc, int client_socket);
        void pong(std::vector<std::string> &vc, int client_socket);
};


#endif