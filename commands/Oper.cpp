#include "Oper.hpp"

Oper::Oper(Client client, std::string name, std::string password) : Command(client, "OPER"), _name(name), _password(password) { }

Oper::~Oper() {}

/*
std::vector<Message> format
- :<server> 381 <nickname> :You are now an IRC operator
*/
std::vector<Message> Oper::execute()
{
	std::vector<Message> messages;
	try {
		checkValidPassword();
		_client.setIsAdmin(true);
		std::vector<int> targetFd;
		targetFd.push_back(_client.getFd());
		messages.push_back(Message(targetFd, RPL_YOUREOPER, _client.getNickName()));
	} catch (std::vector<Message> &e) {
		messages.push_back(e[0]);
	}
	return (messages);
}

void Oper::checkValidPassword()
{
	// if (_name != Server::getAdminName() || _password != Server::getAdminPassword())
	if (_name != "admin" || _password != "admin")
	{
		std::vector<int> targetFd;
		targetFd.push_back(_client.getFd());
		std::vector<Message> messages;
		messages.push_back(Message(targetFd, 464, _client.getNickName()));
		throw (messages);
	}
}
