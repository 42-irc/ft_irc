#include "Join.hpp"

Join::Join(Client* client, const std::string& channel) : Command(client, "JOIN"), _channel(channel) {}

Join::~Join() {}

void Join::checkValidName(const std::string& name) {
	if ((name[0] != '#' && name[0] != '&') || name.size() > 200) {
		std::vector<int> targetFd;

		targetFd.push_back(_client->getFd());
		throw Message(targetFd, ERR_NOSUCHCHANNEL, name);
	}
}

void Join::checkChannelNum() {
	if (_client->getJoinedChannels().size() > 20) {
		std::vector<int> targetFd;
		std::vector<Message> messages;
		
		targetFd.push_back(_client->getFd());
		throw Message(targetFd, 405, _client->getNickName() + " " + _channel);
	}
}

/*
	prefix JOIN :channel
*/
void Join::execute(){
	std::vector<std::string> targetChannels = ft::split(_channel, ',');
	std::vector<std::string>::const_iterator it = targetChannels.begin();
	std::vector<std::string>::const_iterator ite = targetChannels.end();
	std::vector<Message> messages;

	for (; it != ite; it++) {
		try {
			Channel* channel = _client->getServer()->findChannel(_client, *it);

			_client->joinChannel(*it);
			messages.push_back(Message(channel->getFds(), getPrefix(), _type + " " + *it));
		} catch (Message &e) {
			try {
				checkValidName(*it);
				checkChannelNum();

				Channel *channel = new Channel(*it, _client);
				
				_client->getServer()->addChannel(channel);
				_client->joinChannel(*it);
				messages.push_back(Message(channel->getFds(), getPrefix(), _type + " " + *it));
			} catch (Message &e) {
				messages.push_back(e);
			}
		}
	}
	sendMessages(messages);
}
