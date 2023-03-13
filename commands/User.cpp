#include "User.hpp"

User::User(Client* client, std::string userName) : Command(client, "USER"), _userName(userName) {}

User::~User() {}

std::vector<Message> User::execute() {
	std::vector<int> targetFd;
	std::vector<Message> messages;
	
	targetFd.push_back(_client->getFd());
	messages.push_back(Message(targetFd, RPL_WELCOME, _client->getNickName()));
	return messages;
}
