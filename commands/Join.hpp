#ifndef JOIN_HPP
# define JOIN_HPP

# include "../Server.hpp"
# include "Command.hpp"

class Join : public Command {
	private:
		std::string _channel;
		std::string _target;
		void checkChannelNum();
		void checkValidName();

	public:
		Join(User client, std::string channel);
		~Join();

		Message execute();
};

#endif