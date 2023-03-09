#ifndef USER_HPP
# define USER_HPP

# include "../Server.hpp"
# include "Command.hpp"

class User : public Command {
	private:
		std::string _userName;

	public:
		User(Client client, std::string userName);
		~User();

		Message execute();
};

#endif