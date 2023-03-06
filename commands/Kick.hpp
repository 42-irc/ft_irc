#ifndef KICK_HPP
# define KICK_HPP

# include <string>
# include "Command.hpp"
# include "User.hpp"

class Kick : public Command
{
	private:
		std::string const	_targetNick;
		std::string const	_targetChannel;
		std::string const	_reason;
		User				_user;

	public:
		Kick(std::string const targetNick, std::string const targetChannel, std::string const reason, User user);
		~Kick();
		Message	execute();
};

#endif