#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <map>
# include <vector>
# include "User.hpp"
# include "Channel.hpp"
# include "Message.hpp"

class Server{
	private:
		int _port;
		static std::map<std::string, Channel> _channels;
		static std::map<std::string, User> _users;
		std::string _password;
		std::string _adminName;
		std::string _adminPassword;

	public:
		Server(int port, std::string password, std::string adminName, std::string adminPassword);
		~Server();
		const int getPort() const;
		static const std::map<std::string, Channel> getChannels() { return (_channels); };
		static const Channel findChannel(User client, std::string name)
		{
			std::map<std::string, Channel>::iterator it = _channels.find(name);
			if (it != _channels.end())
				return (it->second);
			std::vector<int> fd;
			fd.push_back(client.getFd());
			throw Message(fd, 403, "ft_irc", "ERROR", name + " :No such channel");
		};
		static const std::map<std::string, User> getUsers() { return (_users); };
		static const User findUser(User client, std::string name)
		{
			std::map<std::string, User>::iterator it = _users.find(name);
			if (it != _users.end())
				return (it->second);
			std::vector<int> fd;
			fd.push_back(client.getFd());
			throw Message(fd, 401, "ft_irc", "ERROR", name + " :No such nick");
		};
		const std::string getPassword() const { return (_password); };
		const std::string getAdminName() const { return (_adminName); };
		const std::string getAdminPassword() const { return (_adminPassword); };
		void addChannel(Channel channel)
		{
			_channels.insert(std::pair<std::string, Channel>(channel.getName(), channel));
		}
		void removeChannel(Channel channel)
		{
			_channels.erase(channel.getName());
		};
		void addUser(User user)
		{
			_users.insert(std::pair<std::string, User>(user.getNickName(), user));
		}
		void removeUser(User user)
		{
			std::map<std::string, Channel>::iterator first = _channels.begin();
			std::map<std::string, Channel>::iterator last = _channels.end();
			while (first != last)
			{
				first->second.removeUser(user);
				first++;
			}
			_users.erase(user.getNickName());
		}
};

#endif