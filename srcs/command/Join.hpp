#ifndef JOIN_HPP
# define JOIN_HPP

#include "Command.hpp"

class Join : public Command {
	private:
		std::string _channel;
		std::string _target;
		void checkChannelNum();
		void checkValidName(const std::string& name);
		const Message channelInfo(Channel* channel) const;
		const Message channelInfoEnd(const std::string& channel) const;

	public:
		Join(Client* client, const std::string& channel);
		~Join();

		void execute();
};

#endif
