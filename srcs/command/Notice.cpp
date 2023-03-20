#include "Notice.hpp"

Notice::Notice(Client* client, const std::string& target, const std::string& msg) : Command(client, "NOTICE"), _target(target), _msg(msg) {}

Notice::~Notice() {}

void Notice::validate() {
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
- :server_name NOTICE <target> :<message>
*/
void Notice::execute() {
	validate();
	std::vector<int> targetFds;
	std::vector<std::string> targetList = split(_target, ',');
	std::vector<std::string>::const_iterator it = targetList.begin();
	std::vector<std::string>::const_iterator ite = targetList.end();

	for (; it != ite; it++) {
		Message msg(SERVER_NAME, _type);
		try {
				Client* target = _client->getServer()->findClient(_client, *it);
				msg.addTarget(target->getFd());
				msg.addParam(*it);
				msg.setTrailer(_msg);
				_messages.push_back(msg);
			} catch (Message& e) {
			_messages.push_back(e);
		}
	}
	sendMessages();
}
