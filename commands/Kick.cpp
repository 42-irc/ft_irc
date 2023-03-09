#include "Kick.hpp"

Kick::Kick(Client client, std::string channel, std::string target, std::string reason) : Command(client, "KICK"), _channel(channel), _target(target), _reason(reason) { }

Kick::~Kick() {}

/*
message format
<clientNick>!<clientName>@<clientHost> KICK <channel> <target> :<reason>
*/
Message Kick::execute() {
	Channel channel = Server::findChannel(_client, _channel);
	checkIsAdmin(channel);
	Client target = channel.findClient(_client, _target);
	channel.removeClient(target);
	std::vector<int> targetFd = channel.getFds();
	return (Message(targetFd, _client.getNickName(), getMsg()));
}

const std::string Kick::getMsg() const
{
	return (_type + " " + _channel + " " + _target + " :" + _reason);
}

void Kick::checkIsAdmin(Channel &channel) {
	if (_client.getIsAdmin() == false && channel.getOperator() != _client) {
		std::vector<int> targetFd;
		targetFd.push_back(_client.getFd());
		throw (Message(targetFd, ERR_CHANOPRIVSNEEDED, _channel));
	}
}
