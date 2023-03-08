# include "Server.hpp"

std::map<std::string, Channel> Server::_channels;
std::map<std::string, Client> Server::_clients;

Server::Server(int port, std::string password, std::string adminName, std::string adminPassword) : _port(port), _password(password), _adminName(adminName), _adminPassword(adminPassword) {};

Server::~Server() {};

const int Server::getPort() const { return (_port); }

const std::map<std::string, Channel> Server::getChannels() { return (_channels); }

const Channel Server::findChannel(Client client, std::string name) {
	std::map<std::string, Channel>::iterator it = _channels.find(name);

	if (it != _channels.end()) return (it->second);

	std::vector<int> fd;
	fd.push_back(client.getFd());
	throw Message(fd, 403, "ft_irc", "ERROR", name + " :No such channel");
	return (Channel());
}

const std::map<std::string, Client> Server::getClients() { return (_clients); }

const Client Server::findClient(Client client, std::string name) {
	std::map<std::string, Client>::iterator it = _clients.find(name);

	if (it != _clients.end()) return (it->second);
	if (!client) throw Message();

	std::vector<int> fd;
	fd.push_back(client.getFd());
	throw Message(fd, 401, "ft_irc", "ERROR", name + " :No such nick");
	return (Client());
}

const std::string Server::getPassword() const { return (_password); }

const std::string Server::getAdminName() const { return (_adminName); }

const std::string Server::getAdminPassword() const { return (_adminPassword); }

void Server::addChannel(Channel channel) {
	_channels.insert(std::pair<std::string, Channel>(channel.getName(), channel));
}

void Server::removeChannel(Channel channel) {
	_channels.erase(channel.getName());
}

void Server::addClient(Client client) {
	_clients.insert(std::pair<std::string, Client>(client.getNickName(), client));
}

void Server::removeClient(Client client) {
	std::map<std::string, Channel>::iterator first = _channels.begin();
	std::map<std::string, Channel>::iterator last = _channels.end();
	
	while (first != last) {
		first->second.removeClient(client);
		first++;
	}
	_clients.erase(client.getNickName());
}
