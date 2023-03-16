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
    ERR_NONICKNAMEGIVEN = 431,
    ERR_ERRONEUSNICKNAME = 432,
    ERR_NICKNAMEINUSE = 433,
    ERR_NOTONCHANNEL = 442,
	ERR_USERONCHANNEL = 443,
	ERR_NOTREGISTERED = 451, 
    ERR_CHANOPRIVSNEEDED = 482,
    RPL_LIST = 322,
    RPL_LISTEND = 323,
    RPL_NAMREPLY = 353,
    RPL_NAMEND = 366,
    RPL_YOUREOPER = 381,
    ERR_NEEDMOREPARAMS = 461,
    ERR_PASSWDMISMATCH = 464,
};
# define CODE_001 ":Welcome to the ft_IRC server"
# define CODE_401 ":No such nick"
# define CODE_403 ":No such channel"
# define CODE_405 ":You have joined too many channels"
# define CODE_421 ":Unknown command"
# define CODE_431 ":No nickname given"
# define CODE_432 ":Erroneus nickname"
# define CODE_433 ":Nickname is already in use"
# define CODE_442 ":Not on that channel"
# define CODE_443 ":User is already on that channel"
# define CODE_451 ":You have not registered"
# define CODE_482 ":You're not an channel operator"
# define CODE_322 ""
# define CODE_353 ""
# define CODE_366 ":End of /NAMES list."
# define CODE_381 ":You are now an IRC operator"
# define CODE_323 ":End of /LIST"
# define CODE_461 ":Not enough parameters"
# define CODE_464 ":Password incorrect"

# define SERVER_NAME "ft_irc"
# define SERVER_PREFIX ":ft_irc"

# define MALLOC_ERR ":Malloc failed\r\n"

class Message {
	private:
		std::vector<int> _targets;
		std::string _prefix;
		std::string _command;
		std::vector<std::string> _params;
		std::string _trailer;

		const std::string codeToString(unsigned int n);
		const std::string getCodeMessage(int code);
		const std::string getMessage();

	public:
		Message();
		Message(unsigned int code);
		Message(std::string prefix, std::string command);
		~Message();

		void sendMessage();

		std::vector<int> getTargets();

		void addTarget(int target);
		void addTargets(std::vector<int> targets);
		void addParam(std::string param);
		void addParams(std::vector<std::string> params);

		void setTrailer(std::string trailer);
};

#endif