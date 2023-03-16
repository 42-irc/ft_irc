#include "Command.hpp"

Command::Command(Client* client, std::string type): _client(client), _type(type), _messages(std::vector<Message>()) {}

Command::~Command() {}

const std::string Command::getPrefix() const {
	return _client->getNickName() + "!" + _client->getName() + "@" + _client->getHostName();
}

void Command::checkClient() {
	if (!_client->getIsVerified()) {
		Message msg(ERR_NOTREGISTERED);

		msg.addTarget(_client->getFd());
		msg.addParam(_client->getNickName());
		_messages.push_back(msg);
		sendMessages();
		close(_client->getFd());
		_client->leaveServer();
		throw std::exception();
	}
}

void Command::sendMessages() {
	std::vector<Message>::iterator it = _messages.begin();
	std::vector<Message>::iterator ite = _messages.end();

	for (; it != ite; it++)
		it->sendMessage();
}
