#ifndef KICK_HPP
# define KICK_HPP

#include "Command.hpp"

class Kick : public Command {
	private:
		std::string _channel;
		std::string _target;
		std::string _reason;
		void checkIsAdmin(Channel* channel);

	public:
		Kick(Client* client, const std::string& channel, const std::string& target, const std::string& reason);
		~Kick();

		void execute();
};

#endif
