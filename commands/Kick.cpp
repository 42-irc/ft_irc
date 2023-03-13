#include "Kick.hpp"

Kick::Kick(Client* client, std::string channel, std::string target, std::string reason) : Command(client, "KICK"), _channel(channel), _target(target), _reason(reason) { }

Kick::~Kick() {}

/*
std::vector<Message> format
<clientNick>!<clientName>@<clientHost> KICK <channel> <target> :<reason>
*/
std::vector<Message> Kick::execute() {
	std::vector<Message> messages;
	try {
		Channel* channel = _client->getServer()->findChannel(_client, _channel);
		checkIsAdmin(channel);
		Client* target = channel->findClient(_client, _target);
		std::vector<int> targetFd = channel->getFds();
		messages.push_back(Message(targetFd, _client->getNickName(), getMsg()));
		target->leaveChannel(_channel);
	}
	catch (Message &e) {
		messages.push_back(e);
	}
	return (messages);
}

const std::string Kick::getMsg() const
{
	return (_type + " " + _channel + " " + _target + " :" + _reason);
}

void Kick::checkIsAdmin(Channel* channel) {
	if (_client->getIsAdmin() == false && channel->getOperator() != _client) {
		std::vector<int> targetFd;
		std::vector<Message> messages;

		targetFd.push_back(_client->getFd());
		throw Message(targetFd, ERR_CHANOPRIVSNEEDED, _channel);
	}
}
