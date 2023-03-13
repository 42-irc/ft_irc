#include <unistd.h>

#include "Pass.hpp"

Pass::Pass(Client* client, const std::string& password) : Command(client, "PASS"), _password(password) {};

Pass::~Pass() {};

void Pass::execute() {
	if (_client->getServer()->getPassword() == _password) {
		_client->setIsVerified(true);
		return ;
	}

	std::vector<int> targets;
	std::vector<Message> messages;

	targets.push_back(_client->getFd());
	messages.push_back(Message(targets, ERR_PASSWDMISMATCH, _client->getNickName()));
	sendMessages(messages);
	close(_client->getFd());
	_client->leaveServer();
};
