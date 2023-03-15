#include "Oper.hpp"

Oper::Oper(Client* client, const std::string& name, const std::string& password) : Command(client, "OPER"), _name(name), _password(password) { }

Oper::~Oper() {}

/*
std::vector<Message> format
- :<server> 381 <nickname> :You are now an IRC operator
*/
void Oper::execute() {
	try {
		checkValidPassword();

		Message msg(RPL_YOUREOPER);

		_client->setIsAdmin(true);
		msg.addTarget(_client->getFd());
		msg.addParam(_client->getNickName());
		_messages.push_back(msg);
	} catch (Message& e) {
		_messages.push_back(e);
	}
	sendMessages();
}

void Oper::checkValidPassword() {
	if (_name != _client->getServer()->getAdminName() || _password != _client->getServer()->getAdminPassword()) {
		Message msg(ERR_PASSWDMISMATCH);

		msg.addTarget(_client->getFd());
		msg.addParam(_client->getNickName());
		throw msg;
	}
}
