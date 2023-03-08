#include "Oper.hpp"

Oper::Oper(User client, std::string name, std::string password) : Command(client, "OPER"), _name(name), _password(password) { }

Oper::~Oper() {}

/*
message format
- :<server> 381 <nickname> :You are now an IRC operator
*/
Message Oper::execute()
{
	User target = Server::findUser(_name);
	target.setIsAdmin(true);
	std::vector<int> targetFd;
	targetFd.push_back(target.getFd());
	return Message(targetFd, 381, "ft_irc", "", ":You are now an IRC operator");
}