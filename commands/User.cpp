#include "User.hpp"

User::User(Client client, std::string userName) : Command(client, "USER"), _userName(userName) {}

User::~User() {}

Message User::execute() {
	std::vector<int> targetFd;
	targetFd.push_back(_client.getFd());
	Message message(targetFd, RPL_WELCOME, _client.getNickName());
	return message;
}
