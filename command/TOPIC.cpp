#include "command.hpp"

/*
- If the client sending the command is not joined to the channel and try to 
  view its topic, the server returns 442.

- If the channel doesn't exist, return 403.

- Anyone who wants to view the topic, at any topic mode, the server returns
  RPL_TOPIC and RPL_TOPICWHOTIME

- If the protected topic mode is set (by default it's set), and a regular user
  wants to change the topic, return 482.

- Who can change the topic:  operators
							 regular users (if topic is not protected)

- When the topic is changed, every member on the channel have to recieve TOPIC
  command with the new topic as argument (or an empty argument if the topic
  was cleared)

? is it necessary to return RPL_NOTOPIC when no topic is set ?
*/

bool	check_chan_cli(ircserv& serv, std::string chan, int client_s) {
	if (serv._channels.find(chan) != serv._channels.end() &&
	!client_in_chan(serv, chan, socket_nick(serv, client_s), -1))
		return (
			numerical_message(serv, client_s, 442, chan + " :Not on channel.."),
			false
		);
	if (serv._channels.find(chan) == serv._channels.end())
		return (
			numerical_message(serv, client_s, 403, chan + " :No such channelQ"),
			false
		);
// 	if ()
// 		serv._channels[chan]->get_topic_op_only() &&
// 		!client_in_chan(serv, chan, socket_nick(serv, client_s), 0)
// 		return (
// 			numerical_message(serv, client_s, 403, chan + " :No such channelQ"),
// 			false
// 		);
	return true;
}

void	send_topic(ircserv& serv, std::string chan, int client_s) {
	std::string	chan_topic = serv._channels[chan]->get_topic();
	// who set the topic last time
	std::string	setter = serv._channels[chan]->get_topic_setter();
	std::time_t	last_modified = serv._channels[chan]->get_topic_time();

	// topic message
	numerical_message(serv, client_s, 332, chan + " :" + chan_topic);
	// topic time and who did set it
	numerical_message(serv, client_s, 333, chan + " " + chan_topic +
											" " + setter + " " +
											to_string(last_modified));
}

void	Command::topic(std::vector<std::string>& vc, int client_socket) {
	std::string	msg;

	// I presume that vc.size() > 1
	if (_ircserv->_channels.empty()) {
		std::cout << "No channels\n";
		return ;
	}
	if (vc.size() < 2) {
		std::cout << "Not enough arguments\n";
		return ;
	}
	if (!check_chan_cli(*_ircserv, vc[1], client_socket)) {
		std::cout << "Error in chan/cli (TOPIC)\n";
		return ;
	}
	if (vc.size() == 2)
		return send_topic(*_ircserv, vc[1], client_socket);
	// check if topic only changeable by ops and client is op 
	if (_ircserv->_channels[vc[1]]->get_topic_op_bool() &&
		!client_in_chan(*_ircserv, vc[1], socket_nick(*_ircserv, client_socket),
						0))
			return (
				numerical_message(*_ircserv, client_socket, 482,
									vc[1] + " :Not a chan op..")
				);
	//						SUCCESS, change the topic
	//check that topic... is set with the correct values, and in case it's empty
	_ircserv->_channels[vc[1]]->set_topic(
							_buffer.erase(0, _buffer.find(":") + 1)
									);
	_ircserv->_channels[vc[1]]->set_topic_setter(
									socket_nick(*_ircserv, client_socket)
											);
	_ircserv->_channels[vc[1]]->set_topic_time(
									std::time(NULL)
											);
	// forward topic changed command to all members in channel
	msg = "\r\n:" + _ircserv->_clients[client_socket]->get_nickname() + "!" + 
			_ircserv->_clients[client_socket]->get_username() + "@" + _ircserv->_clients[client_socket]->get_hostname() + " TOPIC " +
			vc[1] + " :" +
			_ircserv->_channels[vc[1]]->get_topic() + "\r\n";
	std::cout << "TOPIC command: " << msg << std::endl;
	forward_to_chan(*_ircserv, vc[1], msg, client_socket, true);
}

