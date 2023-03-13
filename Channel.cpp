#include "Channel.hpp"

Channel::Channel() : _clients(std::map<std::string, Client*>()), _name(""), _operator(NULL) {};

Channel::Channel(std::string name, Client* oper) : _name(name), _operator(oper) {};

Channel::~Channel() {};

const std::string Channel::getName() const { return _name; }

const std::map<std::string, Client*> Channel::getClients() const { return _clients; }

const std::vector<int> Channel::getFds() const {
	std::vector<int> fds;
	std::map<std::string, Client*>::const_iterator first = _clients.begin();
	std::map<std::string, Client*>::const_iterator last = _clients.end();

	while (first != last) {
		fds.push_back(first->second->getFd());
		first++;
	}
	return fds;
}

const std::vector<int> Channel::getFdsExceptClient(Client* client) const {
	std::vector<int> fds;
	std::map<std::string, Client*>::const_iterator first = _clients.begin();
	std::map<std::string, Client*>::const_iterator last = _clients.end();

	while (first != last) {
		if (*first->second != *client)
			fds.push_back(first->second->getFd());
		first++;
	}
	return fds;
}

Client* Channel::findClient(Client* client, std::string name) const {
	std::map<std::string, Client*>::const_iterator it = _clients.find(name);

	if (it != _clients.end())
		return it->second;
	std::vector<int> fd;

	fd.push_back(client->getFd());
	throw Message(fd, ERR_NOSUCHNICK, name);
}

bool Channel::checkClientExist(std::string name) const {
	std::map<std::string, Client*>::const_iterator it = _clients.find(name);

	if (it != _clients.end())
		return true;
	return false;
}

const Client* Channel::getOperator() const {
	return _operator;
}

void Channel::addClient(Client* client) {
	_clients.insert(std::pair<std::string, Client*>(client->getNickName(), client));
}

void Channel::removeClient(Client* client) {
	_clients.erase(client->getNickName());
	if(_operator && (*_operator == *client))
		_operator = NULL;
}