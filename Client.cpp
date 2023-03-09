#include "Client.hpp"

Client::Client(): _isAdmin(false), _fd(-1) {}

Client::Client(int fd): _isAdmin(false), _fd(fd) {}

Client::~Client() {}

const std::string Client::getName() const { return _name; }

const std::string Client::getNickName() const { return _nickName; }

const std::string Client::getHostName() const { return _hostName; }

int Client::getFd() const { return _fd; }

bool Client::getIsAdmin() const { return _isAdmin; }

void Client::setName(const std::string name) { _name = name; }

void Client::setNickName(const std::string nickName) { _nickName = nickName; }

void Client::setHostName(const std::string hostName) { _hostName = hostName; }

void Client::setIsAdmin(const bool isAdmin) { _isAdmin = isAdmin; }

void Client::addChannel(Channel channel) {
	_joinedChannels.insert(std::pair<std::string, Channel>(channel.getName(), channel));
}

void Client::removeChannel(Channel channel) {
	_joinedChannels.erase(channel.getName());
}

bool Client::operator==(const Client &client) const { return _nickName == client._nickName; }

bool Client::operator!=(const Client &client) const { return _nickName != client._nickName; }
