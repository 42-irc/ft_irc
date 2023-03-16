#include "Command.hpp"

Command::Command(Client* client, std::string type): _client(client), _type(type), _messages(std::vector<Message>()) {}

Command::~Command() {}

const std::string Command::getPrefix() const {
	return _client->getNickName() + "!" + _client->getName() + "@" + _client->getHostName();
}

bool Command::checkAuthClient() {
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
