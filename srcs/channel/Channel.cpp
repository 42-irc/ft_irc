#include "Channel.hpp"

Channel::Channel() : _clients(std::map<std::string, Client*>()), _name(""), _operator(NULL) {};

Channel::Channel(const std::string& name, Client* oper) : _clients(std::map<std::string, Client*>()), _name(name), _operator(oper) {};

Channel::~Channel() {};

const std::string Channel::getName() const { return _name; }

const std::map<std::string, Client*> Channel::getClients() const { return _clients; }

const std::vector<int> Channel::getFds() const {
	std::vector<int> fds = std::vector<int>(0);
	std::map<std::string, Client*>::const_iterator it = _clients.begin();
	std::map<std::string, Client*>::const_iterator ite = _clients.end();

	for (; it != ite; it++)
		fds.push_back(it->second->getFd());
	return fds;
}

const std::vector<int> Channel::getFdsExceptClient(Client* client) const {
	std::vector<int> fds = std::vector<int>(0);
	std::map<std::string, Client*>::const_iterator it = _clients.begin();
	std::map<std::string, Client*>::const_iterator ite = _clients.end();

	for (; it != ite; it++) {
		if (*it->second != *client)
			fds.push_back(it->second->getFd());
	}
	return fds;
}

Client* Channel::findClient(Client* client, const std::string& name) const {
	if (client->getServer()->getBot() == client)
		return client;

	std::map<std::string, Client*>::const_iterator it = _clients.find(name);

	if (it != _clients.end())
		return it->second;

	std::vector<int> fd;

	fd.push_back(client->getFd());
	throw Message(fd, ERR_NOSUCHNICK, name);
}

bool Channel::checkClientExist(const std::string& name) const {
	std::map<std::string, Client*>::const_iterator it = _clients.find(name);

	return it != _clients.end();
}

const Client* Channel::getOperator() const {
	return _operator;
}

void Channel::addClient(Client* client) {
	_clients.insert(std::pair<std::string, Client*>(client->getNickName(), client));
}

void Channel::removeClient(Client* client) {
	_clients.erase(client->getNickName());
	if (_operator && (*_operator == *client))
		_operator = NULL;
}