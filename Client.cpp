#include "Client.hpp"

Client::Client():  _fd(-1), _isAdmin(false) {}

Client::Client(int fd): _fd(fd), _isAdmin(false) {}

Client::~Client() {}

const std::string Client::getName() const { return _name; }

const std::string Client::getNickName() const { return _nickName; }

const std::string Client::getHostName() const { return _hostName; }

int Client::getFd() const { return _fd; }

bool Client::getIsAdmin() const { return _isAdmin; }

const std::set<std::string> Client::getChannels() const { return _joinedChannels; }

void Client::setName(const std::string name) { _name = name; }

void Client::setNickName(const std::string nickName) { _nickName = nickName; }

void Client::setHostName(const std::string hostName) { _hostName = hostName; }

void Client::setIsAdmin(const bool isAdmin) { _isAdmin = isAdmin; }

void Client::addChannel(std::string channel) {
	_joinedChannels.insert(channel);
}

void Client::removeChannel(std::string channel) {
	_joinedChannels.erase(channel);
}

bool Client::operator==(const Client &client) const { return _nickName == client._nickName; }

bool Client::operator!=(const Client &client) const { return _nickName != client._nickName; }
