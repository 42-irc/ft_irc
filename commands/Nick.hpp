#ifndef NICK_HPP
# define NICK_HPP

# include <string>
# include "Command.hpp"
# include "User.hpp"

class Nick : public Command
{
	private:
		std::string _nick;

	public:
		Nick(std::string nick, User user);
		~Nick();
		Message	execute();
};

#endif