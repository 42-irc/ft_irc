#include "Join.hpp"

Join::Join(User client, std::string channel) : Command(client, "JOIN"), _channel(channel) {
	_client = client;
}

Join::~Join() {
}

void Join::checkValidName() {
	if ((_channel[0] != '#' && _channel[0] != '&') || _channel.size() > 200){
		std::vector<int> targetFd;
		targetFd.push_back(_client.getFd());
		throw Message(targetFd, 403, _client.getNickName(), ":Invalid channel name", _channel);
	}
}

void Join::checkChannelNum() {
	if (Server::getChannels().size() > 2){
		std::vector<int> targetFd;
		targetFd.push_back(_client.getFd());
		throw Message(targetFd, 405, _client.getNickName(), ":You have joined too many channels", _channel);
	}
}
/*
	prefix JOIN :channel
*/
Message Join::execute(){
	Channel channel;
	try{
		channel = Server::findChannel(_client, _channel);
	}
	catch (Message &e){
		checkValidName();
		checkChannelNum();
		std::vector<int> targetFd;
		targetFd.push_back(_client.getFd());
		channel = Channel(_channel, _client);
		Server::addChannel(channel);
	}
	channel.addUser(_client);
	return Message(channel.getFds(), 0, _client.getNickName(), _type, ": " +  _channel);
}