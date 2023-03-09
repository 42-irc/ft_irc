#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <string>
#include <iostream>
#include <map>

#include "Channel.hpp"

class Channel;

class Client {
	private:
		int _fd;
		std::string _name;
		std::string _nickName;
		std::string _hostName;
		std::map<std::string, Channel> _joinedChannels;
		bool _isAdmin;

	public:
		Client();
		Client(int fd);
		~Client();
		const std::string getName() const;
		const std::string getNickName() const;
		const std::string getHostName() const;
		int getFd() const;
		bool getIsAdmin() const;
		void setName(const std::string name);
		void setNickName(const std::string nickName);
		void setHostName(const std::string hostName);
		void setIsAdmin(const bool isAdmin);
		void addChannel(Channel channel);
		void removeChannel(Channel channel);
		bool operator==(const Client &client) const;
		bool operator!=(const Client &client) const;
};

#endif