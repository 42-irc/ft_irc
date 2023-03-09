#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <string>
# include <iostream>

class Client {
	private:
		std::string _name;
		std::string _nickName;
		std::string _hostName;
		bool _isAdmin;
		int _fd;
		bool checkNickName(std::string nickName);

	public:
		Client();
		Client(int fd);
		Client(int fd, std::string name, std::string nickName, std::string hostName);
		~Client();
		const std::string getName() const;
		const std::string getNickName() const;
		const int getFd() const;
		bool getIsAdmin() const;
		void setName(const std::string name);
		void setNickName(const std::string nickName);
		void setHostName(const std::string hostName);
		void setIsAdmin(const bool isAdmin);
		bool operator==(const Client &client) const;
		bool operator!=(const Client &client) const;
};

#endif