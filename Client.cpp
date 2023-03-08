#include "Client.hpp"
#include "Server.hpp"

Client::Client(): _name(""), _nickName(""), _isAdmin(false), _fd(-1) {}

Client::Client(int fd, std::string name, std::string nickName): _fd(fd), _isAdmin(false) {
	if (name.length() == 0 || nickName.length() == 0) throw;
	if (!checkNickName(nickName)) throw Message();
	_name = name;
	_nickName = nickName;
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

const std::string Client::getName() const { return this->_name; }

const std::string Client::getNickName() const { return this->_nickName; }

const int Client::getFd() const { return this->_fd; }

bool Client::getIsAdmin() const { return this->_isAdmin; }

void Client::setNickName(const std::string nickName) { 
	if (!checkNickName(nickName)) throw;
	this->_nickName = nickName;
}

void Client::setIsAdmin(const bool isAdmin) {
	this->_isAdmin = isAdmin;
}

bool Client::operator==(const Client &client) const { return (_nickName == client._nickName); }

bool Client::operator!=(const Client &client) const { return (_nickName != client._nickName); }
