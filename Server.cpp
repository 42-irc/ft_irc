# include "Server.hpp"

int Server::_port;
std::map<std::string, Channel*> Server::_channels;
std::map<std::string, Client*> Server::_clients;
std::map<int, Client*> Server::_clientsFd;
std::string Server::_password;
std::string Server::_adminName = "admin";
std::string Server::_adminPassword = "admin";

Server::Server(int port, std::string password, std::string adminName, std::string adminPassword) {
	_port = port;
	_password = password;
	_adminName = adminName;
	_adminPassword = adminPassword;
}

Server::~Server() {
	std::map<std::string, Channel*>::iterator it = _channels.begin();
	std::map<std::string, Channel*>::iterator ite = _channels.end();

	for (; it != ite; it++) {
		delete it->second;
	}

	std::map<std::string, Client*>::iterator it2 = _clients.begin();
	std::map<std::string, Client*>::iterator it2e = _clients.end();

	for (; it2 != it2e; it2++) {
		delete it2->second;
	}
};

int Server::getPort() { return _port; }

void Server::setPort(int port) { _port = port; };

std::map<std::string, Channel*> Server::getChannels() { return _channels; }

Channel* Server::findChannel(Client* client, std::string name) {
	std::map<std::string, Channel*>::iterator it = _channels.find(name);

	if (it != _channels.end())
		return it->second;

	std::vector<int> fd;

	fd.push_back(client->getFd());
	throw Message(fd, ERR_NOSUCHCHANNEL, name);
}

std::map<std::string, Client*> Server::getClients() { return _clients; }

Client* Server::findClient(Client* client, std::string name) {
	std::map<std::string, Client*>::iterator it = _clients.find(name);

	if (it != _clients.end())
		return it->second;

	std::vector<int> fd;

	fd.push_back(client->getFd());
	throw Message(fd, ERR_NOSUCHNICK, name);
}

Client* Server::findClient(int fd) {
	std::map<int, Client*>::iterator it = _clientsFd.find(fd);

	if (it != _clientsFd.end())
		return it->second;

	throw Message();
}

const std::string Server::getPassword() { return _password; }

void Server::setPassword(std::string password) { _password = password; }

const std::string Server::getAdminName() { return _adminName; }

const std::string Server::getAdminPassword() { return _adminPassword; }

void Server::addChannel(Channel* channel) {
	_channels.insert(std::pair<std::string, Channel*>(channel->getName(), channel));
}

void Server::removeChannel(Channel* channel) {
	_channels.erase(channel->getName());
}

void Server::addClient(Client* client) {
	_clients[client->getNickName()] = client;
	_clientsFd[client->getFd()] = client;
}

void Server::removeClient(Client* client) {
	std::set<std::string> channels = client->getJoinedChannels();
	std::set<std::string>::iterator first = channels.begin();
	std::set<std::string>::iterator last = channels.end();
	
	while (first != last) {
		removeClientFromChannel(client, _channels[*first]);
		first++;
	}
	_clients.erase(client->getNickName());
	if (_clientsFd.find(client->getFd())->second->getNickName() == client->getNickName())
		_clientsFd.erase(client->getFd());
	delete client;
}

void Server::addClientToChannel(Client* client, Channel* channel) {
	_channels[channel->getName()]->addClient(client);
	_clients[client->getNickName()]->addChannel(channel->getName());
}

void Server::removeClientFromChannel(Client* client, Channel* channel) {
	_channels[channel->getName()]->removeClient(client);
	_clients[client->getNickName()]->removeChannel(channel->getName());
	if (channel->getClients().size() == 0) {
		Server::removeChannel(channel);
		delete channel;
	}
}
