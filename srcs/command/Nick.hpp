#ifndef NICK_HPP
# define NICK_HPP

#include "Command.hpp"

class Nick : public Command {
	private:
		std::string _rawNick;
		std::string _nick;
		const std::string getPrefix(const std::string& oldNick) const;
		void checkValidNick();

	public:
		Nick(Client* client, const std::string& nick);
		~Nick();

		void validate();
		void execute();
};

#endif
