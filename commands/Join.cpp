#include "Join.hpp"

Join::Join(Client client, std::string channel) : Command(client, "JOIN"), _channel(channel) {}

Join::~Join() {}

void Join::checkValidName(std::string& name) {
	if ((name[0] != '#' && name[0] != '&') || name.size() > 200){
		std::vector<int> targetFd;
		targetFd.push_back(_client.getFd());
		std::vector<Message> messages;
		messages.push_back(Message(targetFd, ERR_NOSUCHCHANNEL, name));
		throw (messages);
	}
}

void Join::checkChannelNum() {
	if (Server::getChannels().size() > 20){
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
	std::vector<std::string> targetList = ft::split(_channel, ',');
	std::vector<std::string>::iterator it = targetList.begin();
	std::vector<std::string>::iterator ite = targetList.end();
	std::vector<Message> messages;
	Channel channel;

	for (; it != ite; it++) {
		try{
			channel = Server::findChannel(_client, *it);
			Server::addClientToChannel(_client, channel);
			messages.push_back(Message(channel.getFds(), _client.getNickName(), _type + " " + *it));
		}
		catch (std::vector<Message> &e){
			std::vector<int> targetFd;
			try {
				checkValidName(*it);
				checkChannelNum();
				targetFd.push_back(_client.getFd());
				channel = Channel(*it, _client);
				Server::addChannel(channel);
				Server::addClientToChannel(_client, channel);
				messages.push_back(Message(channel.getFds(), _client.getNickName(), _type + " " + *it));
			} catch (std::vector<Message> &e) {
				messages.push_back(e[0]);
			}
		}
	}
	return messages;
}