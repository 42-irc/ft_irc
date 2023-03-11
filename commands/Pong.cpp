#include "Pong.hpp"

Pong::Pong(Client* client) : Command(client, "PONG") {}

Pong::~Pong() {}

std::vector<Message> Pong::execute() {
	std::vector<Message> messages;
	std::vector<int> targetFd;

	targetFd.push_back(_client->getFd());
	messages.push_back(Message(targetFd, 0, "PING"));
	return messages;
}