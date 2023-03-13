#include "Nick.hpp"

Nick::Nick(Client* client, const std::string& nick) : Command(client, "NICK"), _nick(nick) {}

Nick::~Nick() {}

std::string Nick::getPrefix(const std::string& oldNick) const {
	return oldNick + "!" + _client->getName() + "@" + _client->getHostName();
}

// 첫 닉네임 설정시에는 중복되는 닉네임 없도록 처리하는 함수
void Nick::renameFirstNick() {
	std::map<std::string, Client*> clients = _client->getServer()->getClients();
	std::map<std::string, Client*>::const_iterator it = clients.find(_nick);
	std::map<std::string, Client*>::const_iterator ite = clients.end();

	for (; it != ite; it = clients.find(_nick))
		_nick += "_";
}

std::vector<Message> Nick::execute() {
	std::vector<int> targetFd;
	std::map<std::string, Client*> clients = _client->getServer()->getClients();
	std::vector<Message> messages;

	if (_client->getNickName() == "") {
		renameFirstNick();
	} else if (clients.find(_nick) != clients.end()) {
		targetFd.push_back(_client->getFd());
		messages.push_back(Message(targetFd, ERR_NICKNAMEINUSE, _client->getNickName()));
		return messages;
	}

	Client* newClient = new Client(*_client);

	newClient->setNickName(_nick);
	newClient->getServer()->addClient(newClient);

	std::set<std::string> channels = _client->getJoinedChannels();
	std::set<std::string>::const_iterator it = channels.begin();
	std::set<std::string>::const_iterator ite = channels.end();
	std::string prefix = getPrefix(_client->getNickName());

	for (; it != ite; it++) {
		Channel* channel = _client->getServer()->findChannel(newClient, *it);

		newClient->joinChannel(*it);
		targetFd = channel->getFdsExceptClient(_client);
		messages.push_back(Message(targetFd, prefix, "NICK " + _nick));
	}
	_client->leaveServer();
	targetFd.push_back(newClient->getFd());
	messages.push_back(Message(targetFd, prefix, "NICK " + _nick));
	return messages;
}
