#include "Channel.hpp"

Channel::Channel(std::string ch_name) {
	_channel_name = ch_name;
	_key_authentification = false;
	_is_invite_only = false;
	_is_user_limit = false;
	_operators_n = 0;

}

Channel::~Channel() {}


