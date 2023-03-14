#ifndef OPER_HPP
# define OPER_HPP

#include "Command.hpp"

class Oper : public Command {
	private:
		std::string _name;
		std::string _password;
		void checkValidPassword();

	public:
		Oper(Client* client, const std::string& name, const std::string& password);
		~Oper();

		void execute();
};

#endif
