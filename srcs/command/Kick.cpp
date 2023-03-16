#include "Kick.hpp"

Kick::Kick(Client* client, const std::string& channel, const std::string& target, const std::string& reason) : Command(client, "KICK"), _channel(channel), _target(target), _reason(reason) { }

Kick::~Kick() {}

void Kick::checkIsAdmin(Channel* channel) {
	if (_client->getIsAdmin() || channel->getOperator() == _client) 
		return ;

	Message msg(ERR_CHANOPRIVSNEEDED);
	msg.addTarget(_client->getFd());
	msg.addParam(_channel);

	throw msg;
}

void Kick::validate() {
	checkAuthClient();
	if (_channel.empty() || _target.empty()) {
		Message msg(ERR_NEEDMOREPARAMS);
		msg.addTarget(_client->getFd());
		msg.addParam(_client->getNickName());
		msg.addParam(_type);
		throw msg;
	}
}

/*
std::vector<Message> format
<clientNick>!<clientName>@<clientHost> KICK <channel> <target> :<reason>
*/
void Kick::execute() {
	validate();
	try {
		Channel* channel = _client->getServer()->findChannel(_client, _channel);
		checkIsAdmin(channel);
		Client* target = channel->findClient(_client, _target);

		Message msg(getPrefix(), _type);

		msg.addTargets(channel->getFds());
		msg.addParam(_channel);
		msg.addParam(_target);
		msg.setTrailer(_reason);

		_messages.push_back(msg);
		target->leaveChannel(_channel);
	} catch (Message& e) {
		_messages.push_back(e);
	}
	sendMessages();
}
