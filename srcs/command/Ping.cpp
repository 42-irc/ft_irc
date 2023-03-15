#include "Ping.hpp"

Ping::Ping(Client* client) : Command(client, "PONG") {}

Ping::~Ping() {}

void Ping::execute() {
	Message msg(SERVER_NAME, _type);

	msg.addTarget(_client->getFd());
	msg.addParam(SERVER_NAME);
	msg.setTrailer(SERVER_NAME);
	_messages.push_back(msg);
	sendMessages();
}
