#include "Client.hpp"

Client::Client() :  _fd(-1), _isAdmin(false) {}

Client::Client(int fd, Server* server) : _fd(fd), _server(server), _isAdmin(false) {
	_server->addClient(this);
}

Client::Client(Client const &client) : _fd(client._fd), _server(client._server), _name(client._name), _nickName(client._nickName), _hostName(client._hostName), _joinedChannels(client._joinedChannels), _isAdmin(client._isAdmin) {}

Client::~Client() {}

 Server* Client::getServer() { return _server; };

const std::string Client::getName() const { return _name; }

const std::string Client::getNickName() const { return _nickName; }

const std::string Client::getHostName() const { return _hostName; }

int Client::getFd() const { return _fd; }

bool Client::getIsAdmin() const { return _isAdmin; }

const std::set<std::string> Client::getJoinedChannels() const { return _joinedChannels; }

void Client::setName(const std::string name) { _name = name; }

void Client::setNickName(const std::string nickName) { _nickName = nickName; }

void Client::setHostName(const std::string hostName) { _hostName = hostName; }

void Client::setIsAdmin(const bool isAdmin) { _isAdmin = isAdmin; }

void Client::joinChannel(std::string target) { 
	_server->findChannel(this, target)->addClient(this);
	_joinedChannels.insert(target);
}

void Client::leaveChannel(std::string target) {
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

bool Client::operator==(const Client &client) const { return _nickName == client._nickName; }

bool Client::operator!=(const Client &client) const { return _nickName != client._nickName; }
