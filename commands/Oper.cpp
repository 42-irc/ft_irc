#include "Oper.hpp"

Oper::Oper(Client* client, const std::string& name, const std::string& password) : Command(client, "OPER"), _name(name), _password(password) { }

Oper::~Oper() {}

/*
std::vector<Message> format
- :<server> 381 <nickname> :You are now an IRC operator
*/
void Oper::execute() {
	std::vector<Message> messages;

	try {
		checkValidPassword();
		_client->setIsAdmin(true);

		std::vector<int> targetFd;

		targetFd.push_back(_client->getFd());
		messages.push_back(Message(targetFd, RPL_YOUREOPER, _client->getNickName()));
	} catch (Message& e) {
		messages.push_back(e);
	}
	sendMessages(messages);
}

void Oper::checkValidPassword() {
	if (_name != _client->getServer()->getAdminName() || _password != _client->getServer()->getAdminPassword()) {
		std::vector<int> targetFd;

		targetFd.push_back(_client->getFd());
		throw Message(targetFd, ERR_PASSWDMISMATCH, _client->getNickName());
	}
}
