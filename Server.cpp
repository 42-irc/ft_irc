# include "Server.hpp"

int Server::_port;
std::map<std::string, Channel> Server::_channels;
std::map<std::string, Client> Server::_clients;
std::map<int, Client> Server::_clientsFd;
std::string Server::_password;
std::string Server::_adminName = "admin";
std::string Server::_adminPassword = "admin";

Server::Server() {};

Server::~Server() {};

int Server::getPort() { return _port; }

void Server::setPort(int port) { _port = port; };

const std::map<std::string, Channel> Server::getChannels() { return _channels; }

const Channel Server::findChannel(Client client, std::string name) {
	std::map<std::string, Channel>::iterator it = _channels.find(name);

	if (it != _channels.end())
		return it->second;

	std::vector<int> fd;
	std::vector<Message> messages;

	fd.push_back(client.getFd());
	messages.push_back(Message(fd, ERR_NOSUCHCHANNEL, name));
	throw messages;
}

const std::map<std::string, Client> Server::getClients() { return _clients; }

const Client Server::findClient(Client client, std::string name) {
	std::map<std::string, Client>::iterator it = _clients.find(name);

	if (it != _clients.end())
		return it->second;

	std::vector<int> fd;
	std::vector<Message> messages;

	fd.push_back(client.getFd());
	messages.push_back(Message(fd, ERR_NOSUCHNICK, name));
	throw messages;
}

const Client Server::findClient(int fd) {
	std::map<int, Client>::iterator it = _clientsFd.find(fd);

	if (it != _clientsFd.end())
		return it->second;

	std::vector<Message> messages;
	
	throw messages;
}

const std::string Server::getPassword() { return _password; }

void Server::setPassword(std::string password) { _password = password; }

const std::string Server::getAdminName() { return _adminName; }

const std::string Server::getAdminPassword() { return _adminPassword; }

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

void Server::addClientToChannel(Client client, Channel channel) {
	_channels[channel.getName()].addClient(client);
	_clients[client.getNickName()].addChannel(channel.getName());
}

void Server::removeClientFromChannel(Client client, Channel channel) {
	_channels[channel.getName()].removeClient(client);
	_clients[client.getNickName()].removeChannel(channel.getName());
	if (channel.getClients().size() == 1)
		Server::removeChannel(channel);
}
