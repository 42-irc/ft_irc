#include "Part.hpp"

Part::Part(Client client, std::string channel) : Command(client, "PART"), _channel(channel) {}

Part::~Part() {}

Message Part::execute(){
	Channel channel;
	channel = Server::findChannel( _client, _channel);
	channel.findClient(_client, _client.getNickName());
	Server::removeClientFromChannel(_client, channel);
	if(channel.getClients().size() == 1)
		Server::removeChannel(channel);
	return Message(channel.getFds(), 0, _client.getNickName(), _type, ": " +  _channel);
}