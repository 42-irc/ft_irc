#include "Oper.hpp"

Oper::Oper(Client client, std::string name, std::string password) : Command(client, "OPER"), _name(name), _password(password) { }

Oper::~Oper() {}

/*
message format
- :<server> 381 <nickname> :You are now an IRC operator
*/
Message Oper::execute()
{
	checkValidPassword();
	_client.setIsAdmin(true);
	std::vector<int> targetFd;
	targetFd.push_back(_client.getFd());
	return Message(targetFd, RPL_YOUREOPER, _client.getNickName());
}

void Oper::checkValidPassword()
{
	// if (_name != Server::getAdminName() || _password != Server::getAdminPassword())
	if (_name != "admin" || _password != "admin")
	{
		std::vector<int> targetFd;
		targetFd.push_back(_client.getFd());
		throw Message(targetFd, 464, _client.getNickName());
	}
}
