#include "Kick.hpp"

Kick::Kick(Client* client, const std::string& channel, const std::string& target, const std::string& reason) : Command(client, "KICK"), _channel(channel), _target(target), _reason(reason) { }

Kick::~Kick() {}

const std::string Kick::getMsg() const {
	return _type + " " + _channel + " " + _target + " :" + _reason;
}

void Kick::checkIsAdmin(Channel* channel) {
	if (_client->getIsAdmin() || channel->getOperator() == _client) 
		return ;
	std::vector<int> targetFd;
	std::vector<Message> messages;

	targetFd.push_back(_client->getFd());
	throw Message(targetFd, ERR_CHANOPRIVSNEEDED, _channel);
}

/*
std::vector<Message> format
<clientNick>!<clientName>@<clientHost> KICK <channel> <target> :<reason>
*/
void Kick::execute() {
	std::vector<Message> messages;

	try {
		Channel* channel = _client->getServer()->findChannel(_client, _channel);
		checkIsAdmin(channel);
		Client* target = channel->findClient(_client, _target);
		std::vector<int> targetFd = channel->getFds();

		messages.push_back(Message(targetFd, _client->getNickName(), getMsg()));
		target->leaveChannel(_channel);
	} catch (Message& e) {
		messages.push_back(e);
	}
	sendMessages(messages);
}
