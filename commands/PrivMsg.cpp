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
		if ((*it)[0] == '#') {
			try {
				Channel* target = Server::findChannel(_client, *it);;
				targetFd = target->getFds(_client);
				messages.push_back(Message(targetFd, getPrefix(), "PRIVMSG " + getMsg(*it)));
			} catch (std::vector<Message> &e) {
				messages.push_back(e[0]);
			}
		} else {
			try {
				Client* target = Server::findClient(_client, *it);
				targetFd.push_back(target->getFd());
				messages.push_back(Message(targetFd, getPrefix(), "PRIVMSG " + getMsg(*it)));
			} catch (std::vector<Message> &e) {
				messages.push_back(e[0]);
			}
		}
	}
	return messages;
}

