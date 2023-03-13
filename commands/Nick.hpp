#ifndef NICK_HPP
# define NICK_HPP

# include "Command.hpp"
# include "../Server.hpp"

class Nick : public Command
{
	private:
		std::string _nick;
		std::string getPrefix(const std::string& oldNick) const;
		void renameFirstNick();

	public:
		Nick(Client* client, const std::string& nick);
		~Nick();

		void execute();
};

#endif
