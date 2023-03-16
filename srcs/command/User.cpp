#include "User.hpp"

User::User(Client* client, const std::string& userName) : Command(client, "USER"), _userName(userName) {}

User::~User() {}

void User::execute() {
	Message msg(RPL_WELCOME);

    _client->setName(_userName);
	msg.addTarget(_client->getFd());
	msg.addParam(_client->getNickName());
	_messages.push_back(msg);
	sendMessages();
}
