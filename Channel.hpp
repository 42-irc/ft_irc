#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <string>
#include <map>
#include "User.hpp"

class Channel {
	private:
		std::string _name;
		std::map<std::string, User> _users;
		User _owner;

	public:
		Channel(std::string name, User owner);
		~Channel();
		const std::string getName() const
		{ return (_name); };
		const std::map<std::string, User> getUsers() const
		{ return (_users); };
		const std::vector<int> getFds() const
		{
			std::vector<int> fds;
			std::map<std::string, User>::const_iterator first = _users.begin();
			std::map<std::string, User>::const_iterator last = _users.end();
			while (first != last)
			{
				fds.push_back(first->second.getFd());
				first++;
			}
			return (fds);
		};
		const User findUser(User client, std::string name) const
		{
			std::map<std::string, User>::const_iterator it = _users.find(name);
			if (it != _users.end())
				return (it->second);
			std::vector<int> fd;
			fd.push_back(client.getFd());
			throw Message(fd, 401, "ft_irc", "ERROR", name + " :No such nick");
		}
		const User getOwner() const;
		void addUser(User user)
		{
			_users.insert(std::pair<std::string, User>(user.getNickName(), user));
		};
		void removeUser(User user)
		{
			_users.erase(user.getNickName());
		};
};

#endif