#ifndef NICK_HPP
# define NICK_HPP

# include <string>
# include "Command.hpp"

class Nick : public Command
{
	private:
		std::string _nick;

	public:
		Nick(std::string nick, Client client);
		~Nick();
		Message	execute();
};

#endif