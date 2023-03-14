# include "Server.hpp"

Server::Server(int port, const std::string& password, const std::string& adminName, const std::string& adminPassword): _port(port), _password(password),_adminName(adminName), _adminPassword(adminPassword) {
	Client *bot = new Client(1, this);
	bot->setNickName("BOT🤖");
	_bot = bot;
}

Server::~Server() {
	std::map<std::string, Channel*>::const_iterator it = _channels.begin();
	std::map<std::string, Channel*>::const_iterator ite = _channels.end();

	for (; it != ite; it++) {
		delete it->second;
	}

	std::map<std::string, Client*>::const_iterator it2 = _clients.begin();
	std::map<std::string, Client*>::const_iterator it2e = _clients.end();

	for (; it2 != it2e; it2++) {
		delete it2->second;
	}
};

Client* Server::getBot() { return _bot; }

int Server::getPort() { return _port; }

std::map<std::string, Channel*> Server::getChannels() { return _channels; }

std::map<std::string, Client*> Server::getClients() { return _clients; }

const std::string Server::getPassword() { return _password; }

const std::string Server::getAdminName() { return _adminName; }

const std::string Server::getAdminPassword() { return _adminPassword; }

void Server::setPort(int port) { _port = port; };

void Server::setPassword(const std::string& password) { _password = password; }

Channel* Server::findChannel(Client* client, const std::string& name) {
	std::map<std::string, Channel*>::const_iterator it = _channels.find(name);

	if (it != _channels.end())
		return it->second;

	std::vector<int> fd;

	fd.push_back(client->getFd());
	throw Message(fd, ERR_NOSUCHCHANNEL, name);
}


Client* Server::findClient(Client* client, const std::string& name) {
	std::map<std::string, Client*>::const_iterator it = _clients.find(name);

	if (it != _clients.end())
		return it->second;

	std::vector<int> fd;

	fd.push_back(client->getFd());
	throw Message(fd, ERR_NOSUCHNICK, name);
}

Client* Server::findClient(int fd) {
	std::map<int, Client*>::const_iterator it = _clientsFd.find(fd);

	if (it != _clientsFd.end())
		return it->second;

	throw Message();
}

void Server::addChannel(Channel* channel) {
	_channels.insert(std::pair<std::string, Channel*>(channel->getName(), channel));
}

void Server::addClient(Client* client) {
	_clients[client->getNickName()] = client;
	_clientsFd[client->getFd()] = client;
}

void Server::removeChannel(Channel* channel) {
	_channels.erase(channel->getName());
}

void Server::removeClient(Client* client) {
	_clients.erase(client->getNickName());
	if (_clientsFd.find(client->getFd())->second->getNickName() == client->getNickName())
		_clientsFd.erase(client->getFd());
	delete client;
}