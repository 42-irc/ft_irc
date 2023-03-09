#include "Part.hpp"

Part::Part(Client client, std::string channel) : Command(client, "PART"), _channel(channel) {}

Part::~Part() {}

std::vector<Message> Part::execute(){
	Channel channel;
	channel = Server::findChannel( _client, _channel);
	channel.findClient(_client, _client.getNickName());
	Server::removeClientFromChannel(_client, channel);
	std::vector<Message> messages;
	messages.push_back(Message(channel.getFds(), _client.getNickName(), _type + " " + _channel));
	return messages;
}