#include "Channel.hpp"

Channel::Channel(std::string ch_name) {
	_channel_name = ch_name;
	_key_authentification = false;
	_is_invite_only = false;
	_is_topic_op_only = true;
	_user_limit = -1;
	_operators_n = 0;
	_default_kick_msg = "You're so fucking annoying";
}

Channel::~Channel() {}

bool	Channel::get_key_bool() const {
// 	return !_key.empty();
	return _key_authentification;
}

bool	Channel::get_invite_bool() const {
	return _is_invite_only;
}

void	Channel::set_invite_bool(bool v) {
	_is_invite_only = v;
}

bool	Channel::get_user_limit_bool() const {
	return (_user_limit < 0) ? false : true;
}

bool	Channel::is_channel_full() const {
	int		members_n = _members.size();
	return members_n == _user_limit;
}

std::string	Channel::get_topic() const {
	return _topic;
}

void	Channel::set_topic(std::string topic){
	_topic = topic;
}

void	Channel::set_key(std::string key){
	_key = key;
}

void	Channel::set_key_bool(bool v){
	_key_authentification = v;
}

bool	Channel::get_topic_op_bool() const {
	return _is_topic_op_only;
}

void	Channel::set_topic_setter(std::string setter) {
	_topic_setter = setter;
}

void	Channel::set_topic_time(std::time_t t) {
	_topic_setter = t;
}

std::string	Channel::get_topic_setter() const {
	return _topic_setter;
}

std::time_t	Channel::get_topic_time() const {
	return _topic_time;
}

void	Channel::set_user_limit_bool(bool v) {
	_user_limit_bool = v;
}

void	Channel::set_topic_op_bool(bool v) {
	_is_topic_op_only = v;
}
