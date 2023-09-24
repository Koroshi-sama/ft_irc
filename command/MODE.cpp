/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 18:30:13 by aerrazik          #+#    #+#             */
/*   Updated: 2023/09/24 15:58:56 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.hpp"

void	mode_invite_only(ircserv& serv, std::string chan, int client_s,
							char action) {
	std::string	msg;
	bool		value = (action == '+') ? true : false;

	if (action == '+' && serv._channels[chan]->get_invite_bool())
		return ;
	if (action == '-' && !serv._channels[chan]->get_invite_bool())
		return ;
	serv._channels[chan]->set_invite_bool(value);
// 	command_message(serv, client_s, "MODE", chan + " " + action + "i");

	msg = "\r\n:" + serv._clients[client_s]->get_nickname() +
		  "!" + serv._clients[client_s]->get_username() +
		  "@localhost MODE " + chan + " " + action + "i\r\n";
	forward_to_chan(serv, chan, msg, client_s, true);
	std::cout << "Mode Invite Only function\n";
}

void	mode_topic(ircserv& serv, std::string chan, int client_s,
							char action) {
	std::string	msg;
	bool		value = (action == '+') ? true : false;

	serv._channels[chan]->set_topic_op_bool(value);

	msg = "\r\n:" + serv._clients[client_s]->get_nickname() +
		  "!" + serv._clients[client_s]->get_username() +
		  "@localhost MODE " + chan + " " + action + "t\r\n";
	forward_to_chan(serv, chan, msg, client_s, true);
	std::cout << "Mode Topic function\n";
}

// void	mode_key(ircserv& serv, std::vector<std::string> vc, int client_s,
void	mode_key(ircserv& serv, std::vector<std::string>& vc, int client_s,
							char action) {
	std::string	msg;
	std::string	current_key = serv._channels[vc[1]]->get_key();
	bool		value = (action == '+') ? true : false;

	if (vc.size() != 4) return ;

	if (
		(action == '+' && !current_key.empty()) ||
		(action == '-' && current_key.compare(vc[3]))
	   )
	   return ;
	
	serv._channels[vc[1]]->set_key_bool(value);
	if (action == '-')
		serv._channels[vc[1]]->set_key("");
	else
		serv._channels[vc[1]]->set_key(vc[3]);

	msg = "\r\n:" + serv._clients[client_s]->get_nickname() +
	  "!" + serv._clients[client_s]->get_username() +
	  "@localhost MODE " + vc[1] + " " + action + "k " +
	  vc[3] + "\r\n";

	forward_to_chan(serv, vc[1], msg, client_s, true);
	std::cout << "Mode Key function\n";
}

std::vector<Client*>::iterator
		member_index(std::vector<Client*>& members, std::string nick) {
	std::vector<Client*>::iterator	it;

	for (it = members.begin(); it != members.end(); it++) {
		if ((*it)->get_nickname().compare(nick) == 0)
			return it;
	}
	return members.end();
}

bool	check_op_req(ircserv& serv, std::vector<std::string>& vc, char action) {
	if (vc.size() != 4)
		return false;

	if (!client_in_chan(serv, vc[1], vc[3], -1))
		return false;
	if (action == '+' &&
		client_in_chan(serv, vc[1], vc[3], 0))
		return false;
	if (action == '-' &&
		!client_in_chan(serv, vc[1], vc[3], 0))
		return false;
	return true;
}

void	mode_op_privileges(ircserv& serv, std::vector<std::string>& vc, int client_s,
							char action) {
	std::vector<Client*>::iterator	member_pos;
	std::vector<Client*>::iterator	members_begin;
	Client*							member;
	std::string						msg;

	if (!check_op_req(serv, vc, action)) {
		std::cout << "Error in operator function................\n";
		return ;}
	
	if (action == '+') {
		serv._channels[vc[1]]->_operators_n++;
		member_pos = member_index(serv._channels[vc[1]]->_members, vc[3]);
		member = *member_pos;
		members_begin = serv._channels[vc[1]]->_members.begin();
		serv._channels[vc[1]]->_members.erase(member_pos);
		serv._channels[vc[1]]->_members.insert(members_begin + 1, member);
	}
	else {
		serv._channels[vc[1]]->_operators_n--; member_pos = member_index(serv._channels[vc[1]]->_members, vc[3]);
		member = *member_pos;
		serv._channels[vc[1]]->_members.erase(member_pos);
		serv._channels[vc[1]]->_members.push_back(member);
	}

	msg = "\r\n:" + serv._clients[client_s]->get_nickname() +
		  "!" + serv._clients[client_s]->get_username() +
		  "@localhost MODE " + vc[1] + " " + action + "o " +
		  vc[3] + "\r\n";

	forward_to_chan(serv, vc[1], msg, client_s, true);
	std::cout << "Mode Operator function\n";
}

bool	check_limit_req(std::vector<std::string>& vc, char action) {
	if ((action == '-' && vc.size() != 3) || // uselesss since when -l any additional arg get joined to one string
		(action == '+' && vc.size() != 4))
		return false;
	if (vc.size() == 4 && vc[3][0] == '-')
		return false;
	if (vc.size() == 4 && std::strtoul(vc[3].c_str(), 0, 10) > 2147483647)
		return false;
	return true;
}

void	mode_user_limit(ircserv& serv, std::vector<std::string>& vc, int client_s,
							char action) {
	bool		b;
	int			limit;
	std::string	msg;

	if (!check_limit_req(vc, action)) {
		std::cout << "Error in User limit req........\n";
		return ;
	}
	if (action == '-' && !serv._channels[vc[1]]->get_user_limit_bool())
		return ;
	
	b = (action == '+') ? true : false;
	if (action == '+') {
		limit = std::atoi(vc[3].c_str());
		if (limit <= 0)
			return ;
		serv._channels[vc[1]]->set_user_limit(limit);
	}
	else
		serv._channels[vc[1]]->set_user_limit(-1);
	serv._channels[vc[1]]->set_user_limit_bool(b);

	msg = "\r\n:" + serv._clients[client_s]->get_nickname() +
		  "!" + serv._clients[client_s]->get_username() +
		  "@localhost MODE " + vc[1] + " " + action + "l";

	if (action == '+')
		msg += " " + to_string(limit);
	msg += "\r\n";

	forward_to_chan(serv, vc[1], msg, client_s, true);
	std::cout << "Mode User Limit function\n";
}

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

	if (vc.size() == 2) {
		std::string replay = "221 RPL_UMODEIS\r\n";
		send(client_socket, replay.c_str(), replay.size() + 1, 0);
		return ;
	}

// ---------------------------------------------------------------

	if ((vc[2][0] != '+' && vc[2][0] != '-')) {
		std::cout << "mode chars are Missing!!!!\n"; 
		return ;
	}
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
			mode_topic(*_ircserv, vc[1], client_socket, action);
			break ;
		case ('k'):
			mode_key(*_ircserv, vc, client_socket, action);
			break ;
		case ('o'):
			mode_op_privileges(*_ircserv, vc, client_socket, action);
			break ;
		case ('l'):
			mode_user_limit(*_ircserv, vc, client_socket, action);
	}
}
