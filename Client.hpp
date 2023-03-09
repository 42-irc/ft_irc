#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <string>
#include <iostream>
#include <set>

class Client {
	private:
		int _fd;
		std::string _name;
		std::string _nickName;
		std::string _hostName;
		std::set<std::string> _joinedChannels;
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
		void addChannel(std::string channel);
		void removeChannel(std::string channel);
		bool operator==(const Client &client) const;
		bool operator!=(const Client &client) const;
};

#endif