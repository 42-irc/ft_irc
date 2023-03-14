#include "Part.hpp"

Part::Part(Client* client, const std::string& channel, const std::string& reason) : Command(client, "PART"), _channel(channel), _reason(reason) {}

Part::~Part() {}

const std::string Part::getMsg(const std::string& channel) const {
	return _type + " " + channel + " " +  _reason;
}

void Part::execute() {
	std::vector<std::string> targetChannels = ft::split(_channel, ',');
	std::vector<std::string>::const_iterator it = targetChannels.begin();
	std::vector<std::string>::const_iterator ite = targetChannels.end();

	for (; it != ite; it++) {
		try {
			Channel* channel = _client->getServer()->findChannel(_client, *it);

			channel->findClient(_client, _client->getNickName());
			_messages.push_back(Message(channel->getFds(), getPrefix(), getMsg(*it)));
			_client->leaveChannel(*it);
		} catch (Message& e) {
			_messages.push_back(e);
		}
	}
	sendMessages();
}
