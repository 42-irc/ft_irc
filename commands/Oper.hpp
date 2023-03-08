#ifndef OPER_HPP
# define OPER_HPP

# include "Command.hpp"
# include "Server.hpp"

class Oper : public Command
{
	private:
		std::string _name;
		std::string _password;
		void checkValidPassword();

	public:
		Oper(User client, std::string name, std::string password);
		~Oper();
		Message	execute();
};

#endif