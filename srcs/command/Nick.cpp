#include <unistd.h>
#include <algorithm>

#include "Nick.hpp"

Nick::Nick(Client* client, const std::string& nick) : Command(client, "NICK"), _rawNick(nick), _nick(nick) {
	std::transform(_nick.begin(), _nick.end(), _nick.begin(), ::tolower);
}

Nick::~Nick() {}

const std::string Nick::getPrefix(const std::string& oldNick) const {
	return oldNick + "!" + _client->getName() + "@" + _client->getHostName();
}

void Nick::checkValidNick() {
	std::map<std::string, Client*> clients = _client->getServer()->getClients();

	if (clients.find(_nick) != clients.end())
		throw Message(ERR_NICKNAMEINUSE);
	if (_nick.size() < 1)
		throw Message(ERR_NONICKNAMEGIVEN);
	if (_nick.size() > 9)
		throw Message(ERR_ERRONEUSNICKNAME);
	for (size_t i = 0; i < _nick.size(); i++) {
		if (!isalnum(_nick[i]) && _nick[i] != '_')
			throw Message(ERR_ERRONEUSNICKNAME);
	}
}

void Nick::validate() {
	if (!_client->getIsVerified()) {
		Message msg(ERR_NOTREGISTERED);

		msg.addTarget(_client->getFd());
		msg.addParam(_client->getNickName());
		throw msg;
	}
}

void Nick::execute() {
	validate();
	try {
		checkValidNick();
	} catch (Message& e) {
		e.addTarget(_client->getFd());
		e.addParam(_client->getNickName());
		e.addParam(_rawNick);
		throw e;
	}

	std::string prefix = _client->getNickName() == "" ? _rawNick : getPrefix(_client->getNickName());
	Client* newClient = new Client(*_client);
	Message msg(prefix, _type);

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
