#include "Join.hpp"

Join::Join(std::string channelName, User user) : _channelName(channelName) {
	_client = user;
}

Join::~Join() {
}


Message Join::checkChannelName() {
	if (_channelName[0] != '#'){
		std::vector<int> targetFd;
		targetFd.push_back(_client.getFd());
		return Message(targetFd, 403, "ERR_NOSUCHCHANNEL", _channelName, ":No such channel");
	}
}

Message Join::checkChannelNum() {
	if (Server::getChannels().size() > 42){
		std::vector<int> targetFd;
		targetFd.push_back(_client.getFd());
		return Message(targetFd, 405, "ERR_TOOMANYCHANNELS", _channelName, ":You have joined too many channels");
	}
}

Message Join::execute(){
	checkChannelName();
	std::map<std::string, Channel> channels = Server::getChannels();
	std::map<std::string, Channel>::iterator it = channels.find(_channelName);
	
	checkChannelNum();
	Channel channel = it->second;
	if (it != channels.end()) {// channel exists
		channel.addUser(_client); // add user to channel
	} else {// channel does not exist -> create
		channel = Channel(_channelName, _client);
		channel.addUser(_client);
		_client.setIsAdmin(true); // first user in channel is admin
		channels.insert(std::pair<std::string, Channel>(_channelName, channel));
	}
	std::map<std::string, User> users = channel.getUsers();
	std::vector<int> targetFd;
	for (std::map<std::string, User>::iterator it2 = users.begin(); it2 != users.end(); it2++) {
		targetFd.push_back(it2->second.getFd());
	}
	return Message(targetFd, 0, _client.getNickName(), "JOIN", _channelName);
}