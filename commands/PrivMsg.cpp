#include "PrivMsg.hpp"

PrivMsg::PrivMsg(Client* client, std::string target, std::string msg) : Command(client, "PRIVMSG"), _target(target), _msg(msg) {}

PrivMsg::~PrivMsg() {}

const std::string PrivMsg::getMsg(const std::string &name) const { return name + " " + _msg; }

/*
std::vector<Message> format
- :<clientNick>!<clientName>@<clientHost> PRIVMSG <target> :<msg>
*/
std::vector<Message> PrivMsg::execute() {
	std::vector<int> targetFd;
	std::vector<Message> messages;
	std::vector<std::string> targetList = ft::split(_target, ',');
	std::vector<std::string>::const_iterator it = targetList.begin();
	std::vector<std::string>::const_iterator ite = targetList.end();

	for (; it != ite; it++) {
		try {
			if ((*it)[0] == '#') {
				Channel* target = _client->getServer()->findChannel(_client, *it);

				target->findClient(_client, _client->getNickName());
				targetFd = target->getFdsExceptClient(_client);
				messages.push_back(Message(targetFd, getPrefix(), "PRIVMSG " + getMsg(*it)));
			} else {
				Client* target = _client->getServer()->findClient(_client, *it);

				targetFd.push_back(target->getFd());
				messages.push_back(Message(targetFd, getPrefix(), "PRIVMSG " + getMsg(*it)));
			}
		} catch (Message &e) {
			messages.push_back(e);
		}
	}
	return messages;
}
