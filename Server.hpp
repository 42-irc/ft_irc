#ifndef SERVER_HPP
# define SERVER_HPP

# include <string>
# include <iostream>
# include <map>
# include <vector>
# include "User.hpp"
# include "Channel.hpp"

class Server{
	private:
		int _port;
		static std::map<std::string, Channel> _channels;
		static std::map<std::string, User> _users;
		std::string _password;
		std::string _adminPassword;

	public:
		Server(int port, std::string password, std::string adminName, std::string adminPassword);
		~Server();
		const int getPort() const;
		static const std::map<std::string, Channel> getChannels();
		static const std::map<std::string, User> getUsers();
		const std::string getPassword() const;
		const std::string getAdminName() const;
		const std::string getAdminPassword() const;
		void addChannel(Channel channel);
		void removeChannel(Channel channel);
		void addUser(User user);
		void removeUser(User user);
};

#endif