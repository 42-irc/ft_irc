#include "Ping.hpp"

Ping::Ping(Client* client) : Command(client, "PING") {}

Ping::~Ping() {}

std::vector<Message> Ping::execute() {
	std::vector<Message> messages;
	std::vector<int> targetFd;

	targetFd.push_back(_client->getFd());
	messages.push_back(Message(targetFd, 0, "PONG"));
	return messages;
}