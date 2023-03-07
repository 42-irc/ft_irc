#ifndef PRIVMSG_HPP
# define PRIVMSG_HPP

# include "Command.hpp"
# include "Server.hpp"

class PrivMsg : public Command
{
	private:
		std::string _target;
		std::string _msg;
		std::vector<int> findTargetUser(std::string target);
		std::vector<int> findTargetChannel(std::string target);
		const std::string getPrefix() const;
		const std::string getMsg() const;

	public:
		PrivMsg(User client, std::string target, std::string msg);
		~PrivMsg();
		Message	execute();
};

#endif