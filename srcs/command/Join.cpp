#include "Join.hpp"

Join::Join(Client* client, const std::string& channel) : Command(client, "JOIN"), _channel(channel) {}

Join::~Join() {}

const std::string Join::getMsg(const std::string& channel) const {
	return _type + " " + channel;
}

void Join::checkValidName(const std::string& name) {
	if ((name[0] == '#' || name[0] != '&') && name.size() <=  200)
		return ;

	std::vector<int> targetFds;

	targetFds.push_back(_client->getFd());
	throw Message(targetFds, ERR_NOSUCHCHANNEL, name);
}

void Join::checkChannelNum() {
	if (_client->getJoinedChannels().size() <= 20)
		return ;

	std::vector<int> targetFds;

	targetFds.push_back(_client->getFd());
	throw Message(targetFds, ERR_TOOMANYCHANNELS, _client->getNickName() + " " + _channel);
}

/*
	prefix JOIN :channel
*/
void Join::execute(){
	std::vector<std::string> targetChannels = ft::split(_channel, ',');
	std::vector<std::string>::const_iterator it = targetChannels.begin();
	std::vector<std::string>::const_iterator ite = targetChannels.end();

	for (; it != ite; it++) {
		try {
			Channel* channel = _client->getServer()->findChannel(_client, *it);

			_client->joinChannel(*it);
			_messages.push_back(Message(channel->getFds(), getPrefix(), getMsg(*it)));
		} catch (Message& e) {
			try {
				std::string bot_msg = ":당신은이방의주인일세";
				checkValidName(*it);
				checkChannelNum();

				Channel *channel = new Channel(*it, _client);
				
				_client->getServer()->addChannel(channel);
				_client->joinChannel(*it);
				_messages.push_back(Message(channel->getFds(), getPrefix(), getMsg(*it)));
				PrivMsg(_client->getServer()->getBot(), *it, bot_msg).execute();
			} catch (Message& e) {
				_messages.push_back(e);
			}
		}
	}
	sendMessages();
}
