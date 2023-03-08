#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <string>
# include <iostream>

class Client {
	private:
		std::string _name;
		std::string _nickName;
		bool _isAdmin;
		int _fd;
		bool checkNickName(std::string nickName);

	public:
		Client();
		Client(int fd, std::string name, std::string nickName);
		~Client();
		const std::string getName() const;
		const std::string getNickName() const;
		const int getFd() const;
		bool getIsAdmin() const;
		void setNickName(const std::string nickName);
		void setIsAdmin(const bool isAdmin);
		bool operator==(const Client &client) const;
		bool operator!=(const Client &client) const;
};

#endif