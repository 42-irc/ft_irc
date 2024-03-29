#include "PrivMsg.hpp"

PrivMsg::PrivMsg(Client* client, const std::string& target, const std::string& msg) : Command(client, "PRIVMSG"), _target(target), _msg(msg) {}

PrivMsg::~PrivMsg() {}

void PrivMsg::validate() {
	checkAuthClient();
	if (_target.empty() || _msg.empty()) {
		Message msg(ERR_NEEDMOREPARAMS);

		msg.addTarget(_client->getFd());
		msg.addParam(_client->getNickName());
		msg.addParam(_type);
		throw msg;
	}
}

/*
std::vector<Message> format
- :<clientNick>!<clientName>@<clientHost> PRIVMSG <target> :<msg>
*/
void PrivMsg::execute() {
	validate();
	std::vector<int> targetFds;
	std::vector<std::string> targetList = split(_target, ',');
	std::vector<std::string>::const_iterator it = targetList.begin();
	std::vector<std::string>::const_iterator ite = targetList.end();

	for (; it != ite; it++) {
		Message msg(getPrefix(), _type);
		try {
			if ((*it)[0] == '#' || (*it)[0] == '&') {
				Channel* target = _client->getServer()->findChannel(_client, *it);

				msg.addTargets(target->getFdsExceptClient(_client));

				target->findClient(_client, _client->getNickName());
			} else {
				Client* target = _client->getServer()->findClient(_client, *it);

				msg.addTarget(target->getFd());
			}
			msg.addParam(*it);
			msg.setTrailer(_msg);
			_messages.push_back(msg);
		} catch (Message& e) {
			_messages.push_back(e);
		}
	}
	sendMessages();
}
