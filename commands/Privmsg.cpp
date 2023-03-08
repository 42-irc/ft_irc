#include "Privmsg.hpp"

PrivMsg::PrivMsg(User client, std::string target, std::string msg) : Command("PRIVMSG"), _target(target), _msg(msg) { _client = client; }

PrivMsg::~PrivMsg() {}

std::vector<int> PrivMsg::findTargetChannel(std::string target)
{
	std::vector<int> targetFd;

	std::map<std::string, Channel> channels = Server::getChannels();
	std::map<std::string, Channel>::iterator targetChannel = channels.find(target);
	if (targetChannel == channels.end()) // 클라이언트가 채널 안에 없는 경우 추가
		throw Message();
	std::map<std::string, User> targetUsers = targetChannel->second.getUsers();
	for (std::map<std::string, User>::iterator it = targetUsers.begin(); it != targetUsers.end(); it++) {
		targetFd.push_back(it->second.getFd());
	}
	return targetFd;
}

std::vector<int> PrivMsg::findTargetUser(std::string target)
{
	std::vector<int> targetFd;

	std::map<std::string, User> users = Server::getUsers();
	std::map<std::string, User>::iterator targetUser = users.find(target);
	if (targetUser == users.end())
		throw Message();
	targetFd.push_back(targetUser->second.getFd());
	return targetFd;
}

const std::string PrivMsg::getPrefix() const
{
	return (_client.getNickName() + "!" + _client.getName() + "@" + _client.getHost());
}

const std::string PrivMsg::getMsg() const { return (_target + " :" + _msg); }

Message	PrivMsg::execute()
{
	std::vector<int> targetFd = _target[0] == '#' ? findTargetChannel(_target) : findTargetUser(_target);
	Message message(targetFd, 0, getPrefix(), "PRIVMSG", getMsg());
	return (message);
}