#ifndef JOIN_HPP
# define JOIN_HPP

# include <string>
# include <iostream>
# include <map>
# include "Message.hpp"
# include "Server.hpp"
# include "Channel.hpp"
# include "Command.hpp"
# include "User.hpp"

class Join : public Command {
	private:
		std::string _channelName;

	public:
		Join(std::string channelName, User user);
		~Join();

		Message checkChannelName();
		Message checkChannelNum();
		Message execute();
};

#endif