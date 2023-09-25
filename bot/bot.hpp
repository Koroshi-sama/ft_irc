#ifndef BOT_HPP
#define BOT_HPP

#include "../server/ircserv.hpp"

class bot {
    private :
        std::string _name;
        std::string _help;
        std::string _rules;
    public :
        bot(std::string name);
        ~bot();
        void help(std::map<int, Client*> clients, std::string channel_name ,int client_socket);
        void rules(std::map<int, Client*> clients, std::string channel_name,int client_socket);
};

void	forward_to_chan(ircserv& serv, std::string chan, std::string msg, int client_s, bool requester_included);

#endif
