#include <unistd.h>

#include "Nick.hpp"

Nick::Nick(Client* client, const std::string& nick) : Command(client, "NICK"), _nick(nick) {}

Nick::~Nick() {}

const std::string Nick::getPrefix(const std::string& oldNick) const {
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
	std::map<std::string, Client*> clients = _client->getServer()->getClients();

	if (_client->getNickName() == "") {
		if (!_client->getIsVerified()) {
			Message msg(ERR_PASSWDMISMATCH);

			msg.addTarget(_client->getFd());
			msg.addParam(_client->getNickName());
			_messages.push_back(msg);
			sendMessages();
			close(_client->getFd());
			_client->leaveServer();
			return ;
		}
		renameFirstNick();
	} else if (clients.find(_nick) != clients.end()) {
		Message msg(ERR_NICKNAMEINUSE);

		msg.addTarget(_client->getFd());
		msg.addParam(_client->getNickName());
		_messages.push_back(msg);
		sendMessages();
		return ;
	}

	Client* newClient = new Client(*_client);
	Message msg(getPrefix(_client->getNickName()), _type);

    newClient->setNickName(_nick);
    newClient->getServer()->addClient(newClient);

	std::set<int> pureTargetFds;
	std::vector<int> targetFds;
	std::set<std::string> channels = _client->getJoinedChannels();
	std::set<std::string>::const_iterator it = channels.begin();
	std::set<std::string>::const_iterator ite = channels.end();

	for (; it != ite; it++) {
		Channel* channel = _client->getServer()->findChannel(newClient, *it);
		std::vector<int> channelFds = channel->getFdsExceptClient(newClient);

		pureTargetFds.insert(channelFds.begin(), channelFds.end());
		newClient->joinChannel(*it);
	}
	_client->leaveServer();
	pureTargetFds.insert(newClient->getFd());
	targetFds.insert(targetFds.begin(),pureTargetFds.begin(), pureTargetFds.end());

	msg.addParam(_nick);
	msg.addTargets(targetFds);
	_messages.push_back(msg);
	sendMessages();
}
