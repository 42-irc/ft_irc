#ifndef KICK_HPP
# define KICK_HPP

# include "Command.hpp"
# include "../Server.hpp"

class Kick : public Command
{
	private:
		std::string _channel;
		std::string _target;
		std::string _reason;
		void checkIsAdmin(Channel* channel);
		const std::string getMsg() const;

	public:
		Kick(Client* client, std::string channel, std::string target, std::string reason);
		~Kick();

		std::vector<Message> execute();
};

#endif
