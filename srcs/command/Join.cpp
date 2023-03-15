#include "Join.hpp"
#include "PrivMsg.hpp"

Join::Join(Client* client, const std::string& channel) : Command(client, "JOIN"), _channel(channel) {}

Join::~Join() {}

const std::string Join::getMsg(const std::string& channel) const {
	return _type + " " + channel;
}

const std::string Join::getChannelInfo(Channel *channel) const {
	std::map<std::string, Client*> clients = channel->getClients();
	std::map<std::string, Client*>::const_iterator it = clients.begin();
	std::map<std::string, Client*>::const_iterator ite = clients.end();
	std::string info = _client->getNickName() + " = " + channel->getName() + " :";

	info += it->second->getNickName();
	it++;
	for (; it != ite; it++) {
		info += " " + it->second->getNickName();
	}

	return info;
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
	Channel *channel;

	for (; it != ite; it++) {
		try {
			channel = _client->getServer()->findChannel(_client, *it);

			_client->joinChannel(*it);
			_messages.push_back(Message(channel->getFds(), getPrefix(), getMsg(*it)));
		} catch (Message& e) {
			try {
				checkValidName(*it);
				checkChannelNum();

				channel = new Channel(*it, _client);
				std::string bot_msg = ":당신은이방의주인일세";

				_client->getServer()->addChannel(channel);
				_client->joinChannel(*it);
				_messages.push_back(Message(channel->getFds(), getPrefix(), getMsg(*it)));
				PrivMsg(_client->getServer()->getBot(), *it, bot_msg).execute();
			} catch (Message& e) {
				_messages.push_back(e);
				continue;
			}
		}
		_messages.push_back(_client->getFd(), RPL_NAMREPLY, getChannelInfo(channel)));
		_messages.push_back(_client->getFd(), RPL_NAMEND, _client->getNickName() + " " + channel->getName()));
	}
	sendMessages();
}
