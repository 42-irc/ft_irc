#include "User.hpp"

User::User(Client* client, const std::string& userName) : Command(client, "USER"), _userName(userName) {}

User::~User() {}

void User::execute() {
	std::vector<int> targetFds;
	
	targetFds.push_back(_client->getFd());
	_messages.push_back(Message(targetFds, RPL_WELCOME, _client->getNickName()));
	sendMessages();
}
