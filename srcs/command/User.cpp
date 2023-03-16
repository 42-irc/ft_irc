#include "User.hpp"

User::User(Client* client, const std::string& userName) : Command(client, "USER"), _userName(userName) {}

User::~User() {}

void User::validate() {
	checkAuthClient();
	if (_userName.empty()) {
		Message msg(ERR_NEEDMOREPARAMS);

		msg.addTarget(_client->getFd());
		msg.addParam(_client->getNickName());
		msg.addParam(_type);
		throw msg;
	}
}

void User::execute() {
	validate();
	Message msg(RPL_WELCOME);

    _client->setName(_userName);
	msg.addTarget(_client->getFd());
	msg.addParam(_client->getNickName());
	_messages.push_back(msg);
	sendMessages();
}
