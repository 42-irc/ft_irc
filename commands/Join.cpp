#include "Join.hpp"

Join::Join(Client client, std::string channel) : Command(client, "JOIN"), _channel(channel) {}

Join::~Join() {}

void Join::checkValidName() {
	if ((_channel[0] != '#' && _channel[0] != '&') || _channel.size() > 200){
		std::vector<int> targetFd;
		targetFd.push_back(_client.getFd());
		std::vector<Message> messages;
		messages.push_back(Message(targetFd, ERR_NOSUCHCHANNEL, _channel));
		throw (messages);
	}
}

void Join::checkChannelNum() {
	if (Server::getChannels().size() > 2){
		std::vector<int> targetFd;
		targetFd.push_back(_client.getFd());
		std::vector<Message> messages;
		messages.push_back(Message(targetFd, 405, _client.getNickName() + " " + _channel));
		throw (messages);
	}
}
/*
	prefix JOIN :channel
*/
std::vector<Message> Join::execute(){
	Channel channel;
	try{
		channel = Server::findChannel(_client, _channel);
	}
	catch (std::vector<Message> &e){
		checkValidName();
		checkChannelNum();
		std::vector<int> targetFd;
		targetFd.push_back(_client.getFd());
		channel = Channel(_channel, _client);
		Server::addChannel(channel);
	}
	Server::addClientToChannel(_client, channel);
	std::vector<Message> messages;
	messages.push_back(Message(channel.getFds(), _client.getNickName(), "JOIN " + _channel));
	return messages;
}