#include "User.hpp"

User::User(Client client, std::string userName) : Command(client, "USER"), _userName(userName) {}

User::~User() {}

std::vector<Message> User::execute() {
	std::vector<int> targetFd;
	targetFd.push_back(_client.getFd());
	std::vector<Message> messages;
	messages.push_back(Message(targetFd, RPL_WELCOME, _client.getNickName()));
	return messages;
}
