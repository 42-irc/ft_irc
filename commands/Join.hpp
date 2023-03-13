#ifndef JOIN_HPP
# define JOIN_HPP

# include "../Server.hpp"
# include "Command.hpp"

class Join : public Command {
	private:
		std::string _channel;
		std::string _target;
		void checkChannelNum();
		void checkValidName(const std::string& name);

	public:
		Join(Client* client, const std::string& channel);
		~Join();

		void execute();
};

#endif
