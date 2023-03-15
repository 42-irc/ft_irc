#ifndef MESSAGE_HPP
# define MESSAGE_HPP

#include <iostream>
#include <sys/socket.h>

#include "utils.hpp"

enum e_code {
	RPL_WELCOME = 001,
	ERR_NOSUCHNICK = 401,
	ERR_NOSUCHCHANNEL = 403,
	ERR_TOOMANYCHANNELS = 405,
	ERR_UNKNOWNCOMMAND = 421,
	ERR_NICKNAMEINUSE = 433,
	ERR_NOTONCHANNEL = 442,
	ERR_CHANOPRIVSNEEDED = 482,
	RPL_LIST = 322,
	RPL_LISTEND = 323,
	RPL_NAMREPLY = 353,
	RPL_NAMEND = 366,
	RPL_YOUREOPER = 381,
	ERR_NEEDMOREPARAMS = 461,
	ERR_PASSWDMISMATCH = 464
};

# define CODE_001 ":Welcome to the ft_IRC server"
# define CODE_401 ":No such nick"
# define CODE_403 ":No such channel"
# define CODE_405 ":You have joined too many channels"
# define CODE_421 ":Unknown command"
# define CODE_433 ":Nickname is already in use"
# define CODE_442 ":Not on that channel"
# define CODE_482 ":You're not an channel operator"
# define CODE_322 ""
# define CODE_353 ""
# define CODE_366 ":End of /NAMES list"
# define CODE_381 ":You are now an IRC operator"
# define CODE_323 ":End of /LIST"
# define CODE_461 ":Not enough parameters"
# define CODE_464 ":Password incorrect"

# define MALLOC_ERR ":Malloc failed\r\n"

class Message {
	private:
		std::vector<int> _targets;
		unsigned int _code;
		std::string _prefix;
		std::string _content;
		const std::string codeToString(unsigned int n);
		const std::string getCodeMessage(int code);
		const std::string getMessage();

	public:
		Message();
		Message(std::vector<int> targets, unsigned int code, const std::string& content);
		Message(std::vector<int> targets, const std::string& prefix, const std::string& content);
		~Message();

		std::vector<int> getTargets();
		void sendMessage();
};

#endif