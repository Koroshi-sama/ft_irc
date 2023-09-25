/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 20:06:14 by aerrazik          #+#    #+#             */
/*   Updated: 2023/09/25 15:59:47 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP

#include "../server/ircserv.hpp"
#include "../bot/bot.hpp"

#define WELCOME 1
#define PASSWORD 485

class ircserv;
class client;

class Command {
    public:

        Command(ircserv *ircserv);
        ~Command();
        void handle_commands(std::string command, int client_socket);
    
    private:
        ircserv *_ircserv;
        bot     _bot;
        typedef void (Command::*CommandFunction)(std::vector<std::string> &, int);
        std::map<std::string, CommandFunction> _commands;
        std::map<std::string, std::vector<std::string> > _params;
		std::string	_buffer;

        void parse_command(std::string command, int client_socket);
        bool check_nickname(std::string nickname);
        void nick(std::vector<std::string> &vc, int client_socket);
        void pass(std::vector<std::string> &vc, int client_socket);
        void user(std::vector<std::string> &vc, int client_socket);
        void quit(std::vector<std::string> &vc, int client_socket);
        void join(std::vector<std::string> &vc, int client_socket);
        void privmsg(std::vector<std::string> &vc, int client_socket);
        void ping(std::vector<std::string> &vc, int client_socket);
        void mode(std::vector<std::string> &vc, int client_socket);
        void kick(std::vector<std::string> &vc, int client_socket);
        void invite(std::vector<std::string> &vc, int client_socket);
        void topic(std::vector<std::string> &vc, int client_socket);
};

// the following 2 functions do opposite operations, the first takes a nickname and returns
// 		a its socket
int			target_socket(std::string nickname, std::map<int, Client*>& clients);
std::string socket_nick(ircserv& serv, int client_s);
bool		client_in_chan(ircserv& serv, std::string& chan, std::string client_nick, int range);
void		send_error(int error, std::string client_nick, int client_s, std::string chan, std::string msg);
void		forward_to_chan(ircserv& serv, std::string chan, std::string msg, int client_s, bool requester_included);
void	    target_channel(int client_s, std::map<int, Client*> clients, std::string target, std::string buffer, ircserv& serv, bot bot);
void		command_message(ircserv& serv, int client_s, std::string command, 
								std::string param);
void		numerical_message(ircserv& serv, int client_s, int num,
								std::string param);
#endif
