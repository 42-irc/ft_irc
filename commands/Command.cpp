#include "Command.hpp"

Command::Command(Client* client, std::string type): _client(client), _type(type) {}

Command::~Command() {}

const std::string Command::getPrefix() const {
	return _client->getNickName() + "!" + _client->getName() + "@" + _client->getHostName();
}
