#include <unistd.h>
#include <algorithm>

#include "Nick.hpp"

Nick::Nick(Client* client, const std::string& nick) : Command(client, "NICK"), _nick(nick) {
	std::transform(_nick.begin(), _nick.end(), _nick.begin(), ::tolower);
}

Nick::~Nick() {}

const std::string Nick::getPrefix(const std::string& oldNick) const {
	return oldNick + "!" + _client->getName() + "@" + _client->getHostName();
}

void Nick::renameFirstNick() {
	std::map<std::string, Client*> clients = _client->getServer()->getClients();
	std::map<std::string, Client*>::const_iterator it = clients.find(_nick);
	std::map<std::string, Client*>::const_iterator ite = clients.end();

	if (it == ite)
		return ;

	const std::string randomCharactor = "abcdefghijklmnopqrstuvwxyz0123456789";
	std::string tmp = _nick;
	unsigned int maxLength = 8;

	if (tmp.size() > maxLength)
		tmp = tmp.substr(0, maxLength);

	while (clients.find(tmp) != ite) {
		if (tmp.size() < maxLength)
			tmp += randomCharactor[rand() % randomCharactor.size()];
		else
			tmp = tmp.substr(0, tmp.size() - 1);
	}
	_nick = tmp;
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
