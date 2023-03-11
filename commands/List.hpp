#ifndef LIST_HPP
# define LIST_HPP

# include "Command.hpp"
# include "../Server.hpp"

class List : public Command
{
	public:
		List(Client* client);
		~List();
		std::vector<Message> execute();
};

#endif