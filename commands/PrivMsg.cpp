#include "PrivMsg.hpp"

PrivMsg::PrivMsg(Client* client, std::string target, std::string msg) : Command(client, "PRIVMSG"), _target(target), _msg(msg) {}

PrivMsg::~PrivMsg() {}

const std::string PrivMsg::getMsg(std::string &name) const { return name + " " + _msg; }

/*
std::vector<Message> format
- :<clientNick>!<clientName>@<clientHost> PRIVMSG <target> :<msg>
*/
std::vector<Message> PrivMsg::execute() {
	std::vector<int> targetFd;
	std::vector<Message> messages;
	std::vector<std::string> targetList = ft::split(_target, ',');
	std::vector<std::string>::iterator it = targetList.begin();
	std::vector<std::string>::iterator ite = targetList.end();

	for (; it != ite; it++) {
		try {
			if ((*it)[0] == '#') { // 채널에 보내는 경우
					Channel* target = _client->getServer()->findChannel(_client, *it); // 채널이 없으면 에러
					target->findClient(_client, _client->getNickName()); // 유저가 채널에 없으면 에러
					targetFd = target->getFdsExceptClient(_client);		 // 자기 자신 제외
					messages.push_back(Message(targetFd, getPrefix(), "PRIVMSG " + getMsg(*it)));
			} else { // 유저에게 보내는 경우
					Client* target = _client->getServer()->findClient(_client, *it); // 유저가 없으면 에러
					targetFd.push_back(target->getFd());
					messages.push_back(Message(targetFd, getPrefix(), "PRIVMSG " + getMsg(*it)));
			}
		} catch (Message &e) {
			messages.push_back(e);
		}
	}
	return messages;
}

