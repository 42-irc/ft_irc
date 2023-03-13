#include "Part.hpp"

Part::Part(Client* client, std::string channel) : Command(client, "PART"), _channel(channel) {}

Part::~Part() {}

std::vector<Message> Part::execute() {
	std::vector<std::string> targetChannels = ft::split(_channel, ',');
	std::vector<std::string>::iterator it = targetChannels.begin();
	std::vector<std::string>::iterator ite = targetChannels.end();
	std::vector<Message> messages;

	for (; it != ite; it++) {
		try {
			Channel* channel = Server::findChannel( _client, *it);
			channel->findClient(_client, _client->getNickName());
			messages.push_back(Message(channel->getFds(), getPrefix(), _type + " " + *it));
			Server::removeClientFromChannel(_client, channel);
		} catch (Message &e) {
			messages.push_back(e);
		}
	}
	return messages;
}