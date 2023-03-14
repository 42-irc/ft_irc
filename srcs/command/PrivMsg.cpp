#include "PrivMsg.hpp"

PrivMsg::PrivMsg(Client* client, const std::string& target, const std::string& msg) : Command(client, "PRIVMSG"), _target(target), _msg(msg) {}

PrivMsg::~PrivMsg() {}

const std::string PrivMsg::getMsg(const std::string& name) const { 
	return _type + " " + name + " " + _msg;
}

/*
std::vector<Message> format
- :<clientNick>!<clientName>@<clientHost> PRIVMSG <target> :<msg>
*/
void PrivMsg::execute() {
	std::vector<int> targetFds;
	std::vector<std::string> targetList = ft::split(_target, ',');
	std::vector<std::string>::const_iterator it = targetList.begin();
	std::vector<std::string>::const_iterator ite = targetList.end();

	for (; it != ite; it++) {
		try {
			if ((*it)[0] == '#') {
				Channel* target = _client->getServer()->findChannel(_client, *it);
				target->findClient(_client, _client->getNickName());

				std::vector<int> channelFds = target->getFdsExceptClient(_client);
				targetFds.insert(targetFds.end(), channelFds.begin(), channelFds.end());
			} else {
				Client* target = _client->getServer()->findClient(_client, *it);
				targetFds.push_back(target->getFd());
			}
		} catch (Message& e) {
			_messages.push_back(e);
		}
	}
	_messages.push_back(Message(targetFds, getPrefix(), getMsg(*it)));
	sendMessages();
}
