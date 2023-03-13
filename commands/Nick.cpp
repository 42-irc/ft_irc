#include "Nick.hpp"

Nick::Nick(Client* client, std::string nick) : Command(client, "NICK"), _nick(nick) {}

Nick::~Nick() {}

std::string Nick::getPrefix(std::string oldNick) const {
	return oldNick + "!" + _client->getName() + "@" + _client->getHostName();
}

// 첫 닉네임 설정시에는 중복되는 닉네임 없도록 처리하는 함수
void Nick::checkFirstNick() {
	std::map<std::string, Client*> clients = _client->getServer()->getClients();
	std::map<std::string, Client*>::const_iterator it = clients.find(_nick);
	std::map<std::string, Client*>::const_iterator end = clients.end();

	if (_client->getNickName() == "") {
		while (it != end) {
			_nick += "_";
			it = clients.find(_nick);
		}
	}
}

std::vector<Message> Nick::execute() {
	std::vector<int> targetFd;
	std::vector<Message> messages;
	std::map<std::string, Client*> clients = _client->getServer()->getClients();
	std::map<std::string, Client*>::const_iterator it = clients.find(_nick);
	std::map<std::string, Client*>::const_iterator end = clients.end();

	if (it != end && _client->getNickName() != "") {
		targetFd.push_back(_client->getFd());
		messages.push_back(Message(targetFd, ERR_NICKNAMEINUSE, _client->getNickName()));
		return messages;
	}
	checkFirstNick();
	std::set<std::string> channels = _client->getJoinedChannels();
	std::set<std::string>::iterator it2 = channels.begin();
	std::set<std::string>::iterator end2 = channels.end();

	std::string prefix = getPrefix(_client->getNickName());
	Client* new_nick = new Client(*_client);
	new_nick->setNickName(_nick);
	new_nick->getServer()->addClient(new_nick);
	while (it2 != end2) {
		Channel* channel = _client->getServer()->findChannel(_client, *it2);
		targetFd = channel->getFdsExceptClient(_client);
		messages.push_back(Message(targetFd, prefix, "NICK " + _nick));
		new_nick->joinChannel(*it2);
		it2++;
	}
	_client->leaveServer();
	targetFd.push_back(new_nick->getFd());
	messages.push_back(Message(targetFd, prefix, "NICK " + _nick));
	return messages;
}
