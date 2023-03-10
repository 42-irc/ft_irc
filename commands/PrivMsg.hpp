#ifndef PRIVMSG_HPP
# define PRIVMSG_HPP

# include "Command.hpp"
# include "../Server.hpp"

class PrivMsg : public Command {
	private:
		std::string _target;
		std::string _msg;
		std::vector<int> findTargetClient(std::string target);
		std::vector<int> findTargetChannel(std::string target);
		const std::string getPrefix() const;
		const std::string getMsg(std::string &name) const;

	public:
		PrivMsg(Client client, std::string target, std::string msg);
		~PrivMsg();
		std::vector<Message> execute();
};

#endif
