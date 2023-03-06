#ifndef MSG_HPP
# define MSG_HPP

# include <string>
# include "Command.hpp"
# include "User.hpp"
# include "Channel.hpp"

class Msg : public Command
{
	private:
		std::string _msg;
		User _user;
		Channel _channel;

	public:
		Msg(std::string msg, User user, Channel channel);
		~Msg();
		Message	execute();
};

#endif