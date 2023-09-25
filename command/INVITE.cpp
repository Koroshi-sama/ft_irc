#include "command.hpp"


// if the channel doesn't exist the server SHOULD reject the command with
//		the ERR_NOSUCHCHANNEL numeric
// if the client issuing the command isn't a member of the target channel
//		reject the command with the ERR_NOTONCHANNEL numeric
// if the channel is invite-only, and the client issuing the command isn't
//		a channel operator, reject the command with ERR_CHANOPRIVSNEEDED numeric
// If the targeted user is already on the target channel, the server MUST
//		reject the command with the ERR_USERONCHANNEL numeric
// 
// When the invite is successful, the server MUST send a RPL_INVITING numeric
// 		to the command issuer, and an INVITE message, with the issuer as <source>,
//		to the target user.
//		Other channel members SHOULD NOT be notified.

bool	client_in_server(ircserv& serv, std::string nickname) {
	std::map<int, Client*>::iterator	it = serv._clients.begin();

	for (; it != serv._clients.end(); it++) {
		if (it->second->get_nickname().compare(nickname) == 0)
			return true;
	}
	return false;
}

bool	check_invite_req(std::vector<std::string>& vc, int client_s, ircserv& serv) {
	bool	is_invite_only;

	if (!client_in_server(serv, vc[1]))
		return (
			numerical_message(serv, client_s, 401, vc[1] +\
					" :No such nick/channel"),
			false
			);
	if (serv._channels.find(vc[2]) == serv._channels.end())
		return (
			numerical_message(serv, client_s, 403, vc[2] + " :No such channel..."),
			false
			);
	is_invite_only = serv._channels[vc[2]]->get_invite_bool();
	if (!is_invite_only && !client_in_chan(serv, vc[2], socket_nick(serv, client_s), -1))
		return (
			numerical_message(serv, client_s, 442, vc[2] +\
					" :You're not on that channel..."),
			false
			);
	if (is_invite_only && !client_in_chan(serv, vc[2], socket_nick(serv, client_s), 0))
		return (
			numerical_message(serv, client_s, 482, vc[2] +\
					" :You're not channel operator..."),
			false
			);
	if (client_in_chan(serv, vc[2], vc[1], 0))
		return (
			numerical_message(serv, client_s, 443, vc[2] +\
					" :is already on channel, yes he already is, yes..."),
			false
			);
	return true;
}

void	Command::invite(std::vector<std::string> &vc, int client_socket) {
	int	target_s;

	if (_ircserv->_channels.empty()) {
		return ;
	}
	if (vc.size() < 2) {
		return ;
	}

	if (!check_invite_req(vc, client_socket, *_ircserv)) {
		return ;
	}
	// Send the invitation msg to the target.
	// Add a function that sends a message command (differentiate between 2 types of
	// messages: success messages (command) and error messages), and look for making the
	// overall code cleaner.

	std::string	msg = "\r\n:" + socket_nick(*_ircserv, client_socket) + " INVITE " + \
					vc[1] + " :" + vc[2] + "\r\n";
	if (send(
		target_socket(vc[1], _ircserv->_clients),
		msg.c_str(),
		msg.size() + 1,
		0) < 0)
		std::cout << "Invite command didn't get send to the target user\n";
	// send success reply to the invite issuer
	numerical_message(*_ircserv, client_socket, 341, vc[1] + " " + vc[2]);
	// add this channel to the vector of channels the target user is invited on

	target_s = target_socket(vc[1], _ircserv->_clients);
	_ircserv->_clients[target_s]->invited_channels.push_back(vc[2]);
}
