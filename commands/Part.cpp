#include "Part.hpp"

Part::Part(Client client, std::string channel) : Command(client, "PART"), _channel(channel) {}

Part::~Part() {}

std::vector<Message> Part::execute(){
	std::vector<std::string> targetList = ft::split(_channel, ',');
	std::vector<std::string>::iterator it = targetList.begin();
	std::vector<std::string>::iterator ite = targetList.end();
	std::vector<Message> messages;

	for (; it != ite; it++) {
		try{
			Channel channel;
			channel = Server::findChannel( _client, *it);
			channel.findClient(_client, _client.getNickName());
			Server::removeClientFromChannel(_client, channel);
			messages.push_back(Message(channel.getFds(), _client.getNickName(), _type + " " + *it));
		}
		catch (std::vector<Message> &e){
			std::vector<int> targetFd;
			std::vector<Message> messages;
			targetFd.push_back(_client.getFd());
			messages.push_back(Message(targetFd, ERR_NOSUCHCHANNEL, *it));
		}
	}
	return messages;
}