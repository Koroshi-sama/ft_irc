#include "bot.hpp"

bot::bot(std::string name) {
    _name = name;
    _help = "# Sure, I can help you! Here are some available commands : - !rules: Displays the channel rules. Feel free to ask any questions or use these commands. Enjoy your time! 😊";
    _rules = "# Before you start chatting, please take a moment to review our channel rules: - Rule 1: Be respectful to fellow members. - Rule 2: No spamming or advertising.- Rule 3: Stay on-topic.";
    
};

bot::~bot(){};

void bot::help(std::map<int, Client*> clients, std::string channel_name, int client_socket) {
    std::string reply = "\r\n:" + clients[client_socket]->get_nickname() + " PRIVMSG " + \
				channel_name + " " + _help + "\r\n";
    send(client_socket, reply.c_str(), reply.size() + 1, 0);
};
void bot::rules(std::map<int, Client*> clients, std::string channel_name,int client_socket){
    std::string reply = "\r\n:" + clients[client_socket]->get_nickname() + " PRIVMSG " + \
				channel_name + " " + _rules + "\r\n";
    send(client_socket, reply.c_str(), reply.size() + 1, 0);
};
