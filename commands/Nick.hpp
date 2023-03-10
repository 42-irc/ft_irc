#ifndef NICK_HPP
# define NICK_HPP

# include "../Server.hpp"
# include "Command.hpp"

class Nick : public Command
{
	private:
		std::string _nick;
	public:
		Nick(Client client ,std::string nick);
		~Nick();
		std::vector<Message> execute();
};

#endif