#include "Client.hpp"
#include "Server.hpp"

Client::Client(): _name(""), _nickName(""), _isAdmin(false), _fd(-1) {}

Client::Client(int fd): _fd(fd), _isAdmin(false) {}

Client::Client(int fd, std::string name, std::string nickName, std::string hostName): _fd(fd), _isAdmin(false) {
	if (name.length() == 0 || nickName.length() == 0) throw;
	if (!checkNickName(nickName)) throw Message();
	_name = name;
	_nickName = nickName;
	_hostName = hostName;
}

Client::~Client() {}

bool Client::checkNickName(std::string nickName) {
	// try {
	// 	Server::findClient(NULL, nickName);
	// } catch (Message &e) {
		if (nickName.find(' ') != std::string::npos
		|| nickName.find(',') != std::string::npos
		|| nickName.find('*') != std::string::npos
		|| nickName.find('?') != std::string::npos
		|| nickName.find('!') != std::string::npos
		|| nickName.find('@') != std::string::npos
		|| nickName.find('$') != std::string::npos
		|| nickName.find(':') != std::string::npos
		|| nickName.find('#') != std::string::npos
		|| nickName.find('.') != std::string::npos) return false;
	// }
	return true;
}

const std::string Client::getName() const { return _name; }

const std::string Client::getNickName() const { return _nickName; }

const int Client::getFd() const { return _fd; }

bool Client::getIsAdmin() const { return _isAdmin; }

void Client::setName(const std::string name) { _name = name; }

void Client::setNickName(const std::string nickName) { 
	if (!checkNickName(nickName)) throw;
	_nickName = nickName;
}

void Client::setHostName(const std::string hostName) { _hostName = hostName; }

void Client::setIsAdmin(const bool isAdmin) {
	_isAdmin = isAdmin;
}

bool Client::operator==(const Client &client) const { return (_nickName == client._nickName); }

bool Client::operator!=(const Client &client) const { return (_nickName != client._nickName); }
