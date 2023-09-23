/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 18:30:13 by aerrazik          #+#    #+#             */
/*   Updated: 2023/09/23 11:38:49 by atouba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

void	mode_invite_only() {}

void	mode_topic() {}

void	mode_key() {}

void	mode_op_privileges() {}

void	mode_user_limit() {}

void Command::mode(std::vector<std::string> &vc, int client_socket) {
    char	mode = vc[2][1];        // could be i | l...
	char	action = vc[2][0];      // could be - | + 

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
