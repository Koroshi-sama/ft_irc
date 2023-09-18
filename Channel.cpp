#include "Channel.hpp"

Channel::Channel() : _current_members_n(0) {}

Channel::Channel(std::string name) : _name(name) {}

Channel::~Channel() {}

std::string	Channel::join(Client* cl) {
	std::string	msg;

	msg = ":" + cl->get_nickname() + " " + get_name() + "\r\n"; // make sure the msg form is correct
	_clients.push_back(*cl);
	return msg;
}

std::string	Channel::get_name() const {
	return _name;
}

unsigned int	Channel::get_current_members_n() const {
	return _clients.size();
}

void	Channel::broadcast_msg_(std::string msg) {
	for (std::vector<Client>::iterator it = _clients.begin(); it != _clients.end(); it++) {
		// private_message to each every client currently in the channel
	}
}
