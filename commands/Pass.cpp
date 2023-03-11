#include "Pass.hpp"

Pass::Pass(Client* client, std::string password) : Command(client, "PASS"), _password(password) {};

Pass::~Pass() {};

std::vector<Message> Pass::execute() {
	std::vector<Message> messages;

	if (Server::getPassword() != _password) {
		std::vector<int> targets;
		
		targets.push_back(_client->getFd());
		messages.push_back(Message(targets, ERR_PASSWDMISMATCH, _client->getNickName()));
	}
	return messages;
};