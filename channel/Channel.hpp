#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "../includes.hpp"
#include "../client/client.hpp"

class Channel {
private:
	std::string			_channel_name;
	bool				_key_authentification;
	bool				_is_invite_only;
	int					_user_limit;
	std::string			_key;

public:
	std::vector<Client>	_members;
	int					_operators_n;

	Channel(std::string);
	~Channel();
	std::string		get_channel_name() const;
	unsigned int	get_current_members_n() const;
	std::string		get_key() const;

	bool			get_key_bool() const;
	bool			get_invite_bool() const;
	bool			get_user_limit_bool() const;

	bool			is_channel_full() const;

	void			join(Client cl);
};

#endif 
