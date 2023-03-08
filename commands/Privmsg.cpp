#include "Privmsg.hpp"

PrivMsg::PrivMsg(User client, std::string target, std::string msg) : Command(client, "PRIVMSG"), _target(target), _msg(msg) {}

PrivMsg::~PrivMsg() {}

const std::string PrivMsg::getPrefix() const
{
	return (_client.getNickName() + "!" + _client.getName() + "@" + _client.getHost());
}

const std::string PrivMsg::getMsg() const { return (_target + " :" + _msg); }

/*
message format
- :<clientNick>!<clientName>@<clientHost> PRIVMSG <target> :<msg>
*/
Message	PrivMsg::execute()
{
	std::vector<int> targetFd;
	if (_target[0] == '#')
	{
		Channel target = Server::findChannel(_client, _target);
		targetFd = target.getFds();
		return (Message(targetFd, 0, getPrefix(), "PRIVMSG", getMsg()));
	}
	User target = Server::findUser(_client, _target);
	targetFd.push_back(target.getFd());
	return (Message(targetFd, 0, getPrefix(), "PRIVMSG", getMsg()));
}