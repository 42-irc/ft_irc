#include "Oper.hpp"

Oper::Oper(Client* client, const std::string& name, const std::string& password) : Command(client, "OPER"), _name(name), _password(password) { }

Oper::~Oper() {}

/*
std::vector<Message> format
- :<server> 381 <nickname> :You are now an IRC operator
*/
void Oper::execute() {
	try {
		std::vector<int> targetFds;

		checkValidPassword();
		_client->setIsAdmin(true);
		targetFds.push_back(_client->getFd());
		_messages.push_back(Message(targetFds, RPL_YOUREOPER, _client->getNickName()));
	} catch (Message& e) {
		_messages.push_back(e);
	}
	sendMessages();
}

void Oper::checkValidPassword() {
	if (_name != _client->getServer()->getAdminName() || _password != _client->getServer()->getAdminPassword()) {
		std::vector<int> targetFds;

		targetFds.push_back(_client->getFd());
		throw Message(targetFds, ERR_PASSWDMISMATCH, _client->getNickName());
	}
}
