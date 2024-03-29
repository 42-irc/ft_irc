#ifndef PRIVMSG_HPP
# define PRIVMSG_HPP

#include "Command.hpp"

class PrivMsg : public Command {
	private:
		std::string _target;
		std::string _msg;

	public:
		PrivMsg(Client* client, const std::string& target, const std::string& msg);
		~PrivMsg();

		void validate();
		void execute();
};

#endif
