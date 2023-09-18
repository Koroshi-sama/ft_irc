#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "includes.hpp"

class Channel {
private:
//  unsigned int			_max_members_n;
//   unsigned int			_current_members_n;
	std::string			_name;
    std::vector<Client>	_clients;
	std::string			_topic;
        
        
public:
	Channel();
	~Channel();

	std::string		join(Client* cl);
	unsigned int	get_current_members_n();
 	void			broadcast_msg_(std::string msg);
};

#endif
