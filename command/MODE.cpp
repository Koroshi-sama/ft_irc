/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 18:30:13 by aerrazik          #+#    #+#             */
/*   Updated: 2023/09/23 14:08:35 by atouba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

void	mode_invite_only() {}

void	mode_topic() {}

void	mode_key() {}

void	mode_op_privileges() {}

void	mode_user_limit() {}

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

    char	mode = vc[2][1];        // could be i | l...
// 	char	action = vc[2][0];      // could be - | + 

	(void)client_socket;
	switch (mode) {
		case ('i'):
			mode_invite_only();
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
