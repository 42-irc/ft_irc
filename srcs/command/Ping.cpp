#include "Ping.hpp"

Ping::Ping(Client* client) : Command(client, "PING") {}

Ping::~Ping() {}

void Ping::execute() {
	std::vector<int> targetFds;

	targetFds.push_back(_client->getFd());
	_messages.push_back(Message(targetFds, 0, "PONG"));
	sendMessages();
}
