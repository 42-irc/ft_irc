#ifndef PART_HPP
# define PART_HPP

# include "Command.hpp"
# include "User.hpp"
# include <vector>

class Part : public Command
{
	private:
		std::vector<std::string> _channelNames;
		User _user;

	public:
		Part(std::vector<std::string> channelNames, User user);
		~Part();
		void	execute();
};

#endif