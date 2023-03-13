#ifndef PRIVMSG_HPP
# define PRIVMSG_HPP

#include "Command.hpp"
#include "../Server.hpp"

class PrivMsg : public Command {
	private:
		std::string _target;
		std::string _msg;
		const std::string getMsg(const std::string &name) const;

	public:
		PrivMsg(Client* client, const std::string& target, const std::string& msg);
		~PrivMsg();

		std::vector<Message> execute();
};

#endif
