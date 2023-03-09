#ifndef USER_HPP
# define USER_HPP

# include "../Server.hpp"
# include "Command.hpp"

class User : public Command {
	private:
		std::string _name;
		std::string _nickName;
		std::string _hostName;

	public:
		User(Client client, std::string name, std::string nickName, std::string hostName);
		~User();

		Message execute();
};

#endif