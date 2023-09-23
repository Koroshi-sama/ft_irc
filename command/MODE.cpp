/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 18:30:13 by aerrazik          #+#    #+#             */
/*   Updated: 2023/09/23 18:34:20 by atouba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

void	mode_invite_only(ircserv& serv, std::string chan, int client_s,
							char action) {
	std::string	msg;
	bool		value = (action == '+') ? true : false;

	serv._channels[chan]->set_invite_bool(value);
// 	command_message(serv, client_s, "MODE", chan + " " + action + "i");

	msg = "\r\n:" + serv._clients[client_s]->get_nickname() +
		  "!" + serv._clients[client_s]->get_username() +
		  "@localhost MODE " + chan + " " + action + "i\r\n";
	forward_to_chan(serv, chan, msg, client_s, true);
	std::cout << "Mode Invite Only function\n";
}

void	mode_topic() {
	
}

void	mode_key() {}

void	mode_op_privileges() {}

void	mode_user_limit() {}

bool	check_mode_req(ircserv& serv, std::string chan, int client_s) {
	if (serv._channels.find(chan) == serv._channels.end())
		return (
			numerical_message(serv, client_s, 403,
								chan + " :No such chan..."),
			false
			);
	// checks client is operator
	if (!client_in_chan(serv, chan, socket_nick(serv, client_s),
						0))
		return (
			numerical_message(serv, client_s, 482,
							chan + " :No chan op..."),
			false
			);
	return true;
}

void Command::mode(std::vector<std::string> &vc, int client_socket) {
// ----------------------------------------------------------------
	std::cout << "Mooooooode" << vc[1] << client_socket << std::endl;
    // Client *client = _ircserv->_clients[client_socket];

	if (vc.size() == 2) {
		std::string replay = "221 RPL_UMODEIS\r\n";
		send(client_socket, replay.c_str(), replay.size() + 1, 0);
		return ;
	}

// ---------------------------------------------------------------

	if (vc[2].size() != 2)
		std::cout << "mode chars are Missing!!!!\n"; 
    char	mode = vc[2][1];        // could be i | l...
	char	action = vc[2][0];      // could be - | + 

	if (!check_mode_req(*_ircserv, vc[1], client_socket)) {
		std::cout << "Error in mode request!!!!\n";
		return ;
	}
	switch (mode) {
		case ('i'):
			mode_invite_only(*_ircserv, vc[1], client_socket, action);
			break ;
		case ('t'):
			mode_topic();
			break ;
		case ('k'):
			mode_key();
			break ;
		case ('o'):
			mode_op_privileges();
			break ;
		case ('l'):
			mode_user_limit();
	}
}
