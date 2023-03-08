# include "Channel.hpp"

Channel::Channel() : _name(""), _owner(User()) {};

Channel::Channel(std::string name, User owner) : _name(name), _owner(owner) {};

Channel::~Channel() {};

const std::string Channel::getName() const {
	return (_name);
}

const std::map<std::string, User> Channel::getUsers() const {
	return (_users);
}

const std::vector<int> Channel::getFds() const {
	std::vector<int> fds;
	std::map<std::string, User>::const_iterator first = _users.begin();
	std::map<std::string, User>::const_iterator last = _users.end();
	while (first != last)
	{
		fds.push_back(first->second.getFd());
		first++;
	}
	return (fds);
}

const User Channel::findUser(User client, std::string name) const {
	std::map<std::string, User>::const_iterator it = _users.find(name);
	if (it != _users.end())
		return (it->second);
	std::vector<int> fd;
	fd.push_back(client.getFd());
	throw Message(fd, 401, "ft_irc", "ERROR", name + " :No such nick");
	return (User());
}

const User Channel::getOwner() const {
	return (_owner);
}

void Channel::addUser(User user) {
	_users.insert(std::pair<std::string, User>(user.getNickName(), user));
}

void Channel::removeUser(User user) {
	_users.erase(user.getNickName());
}