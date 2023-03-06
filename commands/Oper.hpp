#ifndef OPER_HPP
# define OPER_HPP

# include <string>
# include "Command.hpp"
# include "User.hpp"

class Oper : public Command
{
	private:
		std::string _name;
		std::string _password;

	public:
		Oper(std::string name, std::string password, User user);
		~Oper();
		Message	execute();
};

#endif