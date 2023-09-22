#include "command.hpp"


// if the channel doesn't exist the server SHOULD reject the command with the ERR_NOSUCHCHANNEL numeric
// if the client issuing the command isn't a member of the target channel reject the command with the ERR_NOTONCHANNEL numeric
// if the channel is invite-only, and the client issuing the command isn't a channel operator, reject the command with ERR_CHANOPRIVSNEEDED numeric
// If the targeted user is already on the target channel, the server MUST reject the command with the ERR_USERONCHANNEL numeric
// 
// When the invite is successful, the server MUST send a RPL_INVITING numeric to the command issuer, and an INVITE message, with the issuer as <source>, to the target user. Other channel members SHOULD NOT be notified.

void	Command::invite(std::vector<std::string> &vc, int client_socket) {
	(void)vc;
	(void)client_socket;
}
