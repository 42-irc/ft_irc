#include <unistd.h>

#include "Pass.hpp"

Pass::Pass(Client* client, const std::string& password) : Command(client, "PASS"), _password(password) {};

Pass::~Pass() {};

void Pass::validate() {
	if (_password.empty()) {
		Message msg(ERR_NEEDMOREPARAMS);

		msg.addTarget(_client->getFd());
		msg.addParam(_client->getNickName());
		msg.addParam("PASS");
		throw msg;
	}	
}

void Pass::execute() {
	validate();
	if (_client->getServer()->getPassword() == _password) {
		_client->setIsVerified(true);
		return ;
	}

	Message msg(ERR_PASSWDMISMATCH);

	msg.addTarget(_client->getFd());
	msg.addParam(_client->getNickName());
	_messages.push_back(msg);

	sendMessages();

	close(_client->getFd());
	_client->leaveServer();
};
