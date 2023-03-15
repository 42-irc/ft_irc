#include "Join.hpp"
#include "PrivMsg.hpp"

Join::Join(Client* client, const std::string& channel) : Command(client, "JOIN"), _channel(channel) {}

Join::~Join() {}

const Message Join::channelInfo(Channel* channel) const {
	Message msg(RPL_NAMREPLY);

	std::map<std::string, Client*> clients = channel->getClients();
	std::map<std::string, Client*>::const_iterator it = clients.begin();
	std::map<std::string, Client*>::const_iterator ite = clients.end();

	msg.addTarget(_client->getFd());
	msg.addParam("=");
	msg.addParam(_client->getNickName());
	msg.addParam(channel->getName());

	std::string trailer;

	for (; it != ite; it++) {
		if (it->second == channel->getOperator())
			trailer += "@";
		trailer += it->second->getNickName() + " ";
	}
	if (trailer.size() > 0)
		trailer = trailer.substr(0, trailer.size() - 1);
	msg.setTrailer(trailer);
	return msg;
}

const Message Join::channelInfoEnd(const std::string& channel) const {
	Message msg(RPL_NAMEND);
	
	msg.addTarget(_client->getFd());
	msg.addParam(_client->getNickName());
	msg.addParam(channel);
	return msg;
}

void Join::checkValidName(const std::string& name) {
	if ((name[0] == '#' || name[0] != '&') && name.size() <=  200)
		return ;

	Message msg(ERR_NOSUCHCHANNEL);
	msg.addTarget(_client->getFd());
	msg.addParam(name);
	throw msg;
}

void Join::checkChannelNum() {
	if (_client->getJoinedChannels().size() <= 20)
		return ;

	Message msg(ERR_TOOMANYCHANNELS);
	msg.addTarget(_client->getFd());
	msg.addParam(_client->getNickName());
	msg.addParam(_channel);

	throw msg;
}

/*
	prefix JOIN :channel
*/
void Join::execute(){
	std::vector<std::string> targetChannels = split(_channel, ',');
	std::vector<std::string>::const_iterator it = targetChannels.begin();
	std::vector<std::string>::const_iterator ite = targetChannels.end();
	Channel *channel;

	for (; it != ite; it++) {
		Message msg(getPrefix(), _type);
		try {
			channel = _client->getServer()->findChannel(_client, *it);

			_client->joinChannel(*it);
			msg.addTargets(channel->getFds());
		} catch (Message& e) {
			try {
				checkValidName(*it);
				checkChannelNum();

				channel = new Channel(*it, _client);
				std::string bot_msg = ": 당신은이방의주인일세";

				_client->getServer()->addChannel(channel);
				_client->joinChannel(*it);

				msg.addTargets(channel->getFds());
				PrivMsg(_client->getServer()->getBot(), *it, bot_msg).execute();
			} catch (Message& e) {
				_messages.push_back(e);
				continue;
			}
		}
		msg.addParam(*it);
		_messages.push_back(msg);
		_messages.push_back(channelInfo(channel));
		_messages.push_back(channelInfoEnd(*it));
	}
	sendMessages();
}
