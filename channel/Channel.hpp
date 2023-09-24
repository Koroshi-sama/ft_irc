#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "../includes.hpp"
#include "../client/client.hpp"

class Channel {
private:
	bool				_key_authentification;
	bool				_is_invite_only;
	bool				_is_topic_op_only;
	bool				_user_limit_bool;
	int					_user_limit;
	std::string			_key;
	std::string			_topic;
	std::string			_topic_setter;
	std::time_t			_topic_time;


public:
	std::string			_channel_name;
	std::vector<Client>	_members;
	int					_operators_n;
	std::string			_default_kick_msg;

	Channel(std::string);
	~Channel();

	std::string		get_channel_name() const;
	unsigned int	get_current_members_n() const;
	std::string		get_key() const;
	std::string		get_topic() const;
	std::string		get_topic_setter() const;
	std::time_t		get_topic_time() const;
	bool			get_key_bool() const;
	bool			get_invite_bool() const;
	bool			get_user_limit_bool() const;
	bool			get_topic_op_bool() const;

	void			set_key(std::string);
	void			set_topic(std::string);
	void			set_topic_setter(std::string);
	void			set_topic_time(std::time_t);

	void			set_key_bool(bool);
	void			set_invite_bool(bool);
	void			set_user_limit_bool(bool);
	void			set_user_limit(int);
	void			set_topic_op_bool(bool);


	bool			is_channel_full() const;

	void			join(Client cl);
};

#endif 
