#ifndef UTILS_HPP
# define UTILS_HPP

#include <string>
#include <vector>
#include <sstream>
#include <map>

enum e_code {
	RPL_WELCOME = 001,
	ERR_NOSUCHNICK = 401,
	ERR_NOSUCHCHANNEL = 403,
	ERR_UNKNOWNCOMMAND = 421,
	ERR_NICKNAMEINUSE = 433,
	ERR_NOTONCHANNEL = 442,
	ERR_CHANOPRIVSNEEDED = 482,
	RPL_LIST = 322,
	RPL_LISTEND = 323,
	RPL_YOUREOPER = 381,
	ERR_NEEDMOREPARAMS = 461,
	ERR_PASSWDMISMATCH = 464
};

# define CODE_001 ":Welcome to the ft_IRC server"
# define CODE_401 ":No such nick"
# define CODE_403 ":No such channel"
# define CODE_421 ":Unknown command"
# define CODE_433 ":Nickname is already in use"
# define CODE_442 ":Not on that channel"
# define CODE_482 ":You're not an channel operator"
# define CODE_322 ""
# define CODE_381 ":You are now an IRC operator"
# define CODE_323 ":End of /LIST"
# define CODE_461 ":Not enough parameters"
# define CODE_464 ":Password incorrect"

namespace ft
{

	std::vector<std::string> split(const std::string &str, char charset, unsigned long n = 0);
	std::vector<std::string> split(const std::string &str, std::string charset);
	const std::string getCodeMessage(int code);
	const std::string codeToString(unsigned int n);

}

#endif