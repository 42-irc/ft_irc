#include "Command.hpp"

Command::Command(Client* client, std::string type): _client(client), _type(type), _messages(std::vector<Message>()) {
	_client->clearBuffer();
}

Command::~Command() {}

const std::string Command::getPrefix() const {
	return _client->getNickName() + "!" + _client->getName() + "@" + _client->getHostName();
}

void Command::checkAuthClient() {
	if (_client->getServer()->getBot() == _client)
		return ;
	if (!_client->getIsVerified() || _client->getNickName() == "*") {
		Message msg(ERR_NOTREGISTERED);

		msg.addTarget(_client->getFd());
		msg.addParam(_client->getNickName());
		throw msg;
	}
}

void Command::sendMessages() {
	std::vector<Message>::iterator it = _messages.begin();
	std::vector<Message>::iterator ite = _messages.end();

	for (; it != ite; it++)
		it->sendMessage();
}
