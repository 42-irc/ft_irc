#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <string>
#include <iostream>
#include <set>
#include "Server.hpp"

class Server;

class Client {
	private:
		int _fd;
		Server* _server;
		std::string _name;
		std::string _nickName;
		std::string _hostName;
		std::set<std::string> _joinedChannels;
		bool _isAdmin;

	public:
		Client();
		Client(int fd, Server* server);
		Client(Client const &client);
		~Client();

		Server* getServer();
		const std::string getName() const;
		const std::string getNickName() const;
		const std::string getHostName() const;
		const std::set<std::string> getJoinedChannels() const;
		int getFd() const;
		bool getIsAdmin() const;

		void setName(const std::string name);
		void setNickName(const std::string nickName);
		void setHostName(const std::string hostName);
		void setIsAdmin(const bool isAdmin);

		void joinChannel(std::string target);
		void leaveChannel(std::string target);
		void leaveServer();

		bool operator==(const Client &client) const;
		bool operator!=(const Client &client) const;
};

#endif