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

void Nick::execute() {
	std::set<int> targetFd;
	std::vector<int> targetFdVector;
	std::map<std::string, Client*> clients = _client->getServer()->getClients();
	std::vector<Message> messages;

	if (_client->getNickName() == "") {
		renameFirstNick();
	} else if (clients.find(_nick) != clients.end()) {
		targetFd.insert(_client->getFd());
		targetFdVector.insert(targetFdVector.begin(), targetFd.begin(), targetFd.end());
		messages.push_back(Message(targetFdVector, ERR_NICKNAMEINUSE, _client->getNickName()));
		sendMessages(messages);
		return ;
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

		std::vector<int> channelFds = channel->getFdsExceptClient(newClient);
		targetFd.insert(channelFds.begin(), channelFds.end());
		newClient->joinChannel(*it);
	}
	_client->leaveServer();
	targetFd.insert(newClient->getFd());
	targetFdVector.insert(targetFdVector.begin(),targetFd.begin(), targetFd.end());
	messages.push_back(Message(targetFdVector, prefix, "NICK " + _nick));
	sendMessages(messages);
}
