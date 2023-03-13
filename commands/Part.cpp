#include "Part.hpp"

Part::Part(Client* client, const std::string& channel) : Command(client, "PART"), _channel(channel) {}

Part::~Part() {}

void Part::execute() {
	std::vector<std::string> targetChannels = ft::split(_channel, ',');
	std::vector<std::string>::const_iterator it = targetChannels.begin();
	std::vector<std::string>::const_iterator ite = targetChannels.end();
	std::vector<Message> messages;

	for (; it != ite; it++) {
		try {
			Channel* channel = _client->getServer()->findChannel(_client, *it);

			channel->findClient(_client, _client->getNickName());
			messages.push_back(Message(channel->getFds(), getPrefix(), _type + " " + *it));
			_client->leaveChannel(*it);
		} catch (Message& e) {
			messages.push_back(e);
		}
	}
	sendMessages(messages);
}
