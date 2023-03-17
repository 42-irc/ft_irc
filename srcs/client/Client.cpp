#include "Client.hpp"

Client::Client() :  _fd(-1), _isVerified(false), _isAdmin(false) {}

Client::Client(int fd, Server* server) : _fd(fd), _server(server), _nickName("*"), _isVerified(false), _isAdmin(false) {
	_server->addClient(this);
}

Client::Client(const Client& client) : _fd(client._fd), _server(client._server), _name(client._name), _nickName(client._nickName), _hostName(client._hostName), _joinedChannels(client._joinedChannels), _isVerified(client._isVerified), _isAdmin(client._isAdmin) {}

Client::~Client() {}

Server* Client::getServer() { return _server; };

const std::string Client::getName() const { return _name; }

const std::string Client::getNickName() const { return _nickName; }

const std::string Client::getHostName() const { return _hostName; }

int Client::getFd() const { return _fd; }

bool Client::getIsAdmin() const { return _isAdmin; }

bool Client::getIsVerified() const { return _isVerified; }

const std::set<std::string> Client::getJoinedChannels() const { return _joinedChannels; }

std::string Client::getBuffer() const { return buffer; }

void Client::clearBuffer() { buffer.clear(); }

void Client::addToBuffer(const std::string& str) { buffer += str; }

void Client::setName(const std::string& name) { _name = name; }

void Client::setNickName(const std::string& nickName) { _nickName = nickName; }

void Client::setHostName(const std::string& hostName) { _hostName = hostName; }

void Client::setIsAdmin(const bool isAdmin) { _isAdmin = isAdmin; }

void Client::setIsVerified(const bool isVerified) { _isVerified = isVerified; }

void Client::joinChannel(const std::string& target) { 
	_server->findChannel(this, target)->addClient(this);
	_joinedChannels.insert(target);
}

void Client::leaveChannel(const std::string& target) {
	Channel *channel = _server->findChannel(this, target);

	channel->removeClient(this);
	_joinedChannels.erase(target);
	if (channel->getClients().size() == 0) {
		_server->removeChannel(channel);
		delete channel;
	}
}

void Client::leaveServer() {
	std::set<std::string> channels = getJoinedChannels();
	std::set<std::string>::const_iterator it = channels.begin();
	std::set<std::string>::const_iterator ite = channels.end();
	
	for (; it != ite; it++)
		leaveChannel(*it);
	_server->removeClient(this);
}

bool Client::operator==(const Client& client) const { return _fd == client._fd; }

bool Client::operator!=(const Client& client) const { return _fd != client._fd; }
