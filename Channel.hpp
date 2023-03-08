#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <string>
#include <map>
#include "User.hpp"
#include "Message.hpp"

class Channel {
	private:
		std::string _name;
		std::map<std::string, User> _users;
		User _owner;

	public:
		Channel();
		Channel(std::string name, User owner);
		~Channel();
		const std::string getName() const;
		const std::map<std::string, User> getUsers() const;
		const std::vector<int> getFds() const;
		const User findUser(User client, std::string name) const;
		const User getOwner() const;
		void addUser(User user);
		void removeUser(User user);
};

#endif