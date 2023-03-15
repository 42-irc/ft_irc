#include <unistd.h>

#include "Pass.hpp"

Pass::Pass(Client* client, const std::string& password) : Command(client, "PASS"), _password(password) {};

Pass::~Pass() {};

void Pass::execute() {
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
