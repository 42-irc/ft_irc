# include "Server.hpp"

std::map<std::string, Channel> Server::_channels;
std::map<std::string, User> Server::_users;

Server::Server(int port, std::string password, std::string adminName, std::string adminPassword) : _port(port), _password(password), _adminName(adminName), _adminPassword(adminPassword) {};

Server::~Server() {};

const int Server::getPort() const { return (_port); }

const std::map<std::string, Channel> Server::getChannels() { return (_channels); };

const Channel Server::findChannel(User client, std::string name) {
	std::map<std::string, Channel>::iterator it = _channels.find(name);
	if (it != _channels.end())
		return (it->second);
	std::vector<int> fd;
	fd.push_back(client.getFd());
	throw Message(fd, 403, "ft_irc", "ERROR", name + " :No such channel");
	return (Channel());
};
const std::map<std::string, User> Server::getUsers() { return (_users); };
const User Server::findUser(User client, std::string name) {
	std::map<std::string, User>::iterator it = _users.find(name);
	if (it != _users.end())
		return (it->second);
	std::vector<int> fd;
	fd.push_back(client.getFd());
	throw Message(fd, 401, "ft_irc", "ERROR", name + " :No such nick");
	return (User());
};

const std::string Server::getPassword() const { return (_password); };

const std::string Server::getAdminName() const { return (_adminName); };

const std::string Server::getAdminPassword() const { return (_adminPassword); };

void Server::addChannel(Channel channel) {
	_channels.insert(std::pair<std::string, Channel>(channel.getName(), channel));
}

void Server::removeChannel(Channel channel) {
	_channels.erase(channel.getName());
};

void Server::addUser(User user) {
	_users.insert(std::pair<std::string, User>(user.getNickName(), user));
}

void Server::removeUser(User user) {
	std::map<std::string, Channel>::iterator first = _channels.begin();
	std::map<std::string, Channel>::iterator last = _channels.end();
	while (first != last)
	{
		first->second.removeUser(user);
		first++;
	}
	_users.erase(user.getNickName());
}
