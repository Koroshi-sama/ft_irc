#include "Channel.hpp"

Channel::Channel(std::string ch_name) {
	_channel_name = ch_name;
	_key_authentification = false;
	_is_invite_only = false;
	_user_limit = -1;
	_operators_n = 0;
	_default_kick_msg = "You're so fucking annoying";
}

Channel::~Channel() {}

bool	Channel::get_key_bool() const {
	return !_key.empty();
}

bool	Channel::get_invite_bool() const {
	return _is_invite_only;
}

bool	Channel::get_user_limit_bool() const {
	return (_user_limit < 0) ? false : true;
}

bool	Channel::is_channel_full() const {
	int		members_n = _members.size();
	return members_n == _user_limit;
}
