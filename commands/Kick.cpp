#include "Kick.hpp"

Kick::Kick(User client, std::string channel, std::string target, std::string reason) : Command(client, "KICK"), _channel(channel), _target(target), _reason(reason) { }

Kick::~Kick() {}

/*
message format
<clientNick>!<clientName>@<clientHost> KICK <channel> <target> :<reason>
*/
Message Kick::execute() {
	Channel channel = Server::findChannel(_channel);
	checkIsAdmin(channel);
	User target = channel.findUser(_target);
	channel.removeUser(target);
	std::vector<int> targetFd = channel.getFds();
	Message message(targetFd, 0, _client.getNickName(), _type, getMsg());
}

const std::string Kick::getMsg() const
{
	return (_channel + " " + _target + " :" + _reason);
}

void Kick::checkIsAdmin(Channel &channel) {
	if (_client.getIsAdmin() == false && channel.getOwner() != _client) {
		std::vector<int> targetFd;
		targetFd.push_back(_client.getFd());
		throw (Message(targetFd, 482, ":ft_irc", "", _channel + " :You're not an channel operator"));
	}
}
