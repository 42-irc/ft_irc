#ifndef MSG_HPP
# define MSG_HPP

# include "Command.hpp"
# include "Server.hpp"

class Msg : public Command
{
	private:
		std::string _target;
		std::string _msg;
		std::vector<int> findTargetUser(std::string target);
		std::vector<int> findTargetChannel(std::string target);
		const std::string getPrefix() const;
		const std::string getMsg() const;

	public:
		Msg(User client, std::string target, std::string msg);
		~Msg();
		Message	execute();
};

#endif