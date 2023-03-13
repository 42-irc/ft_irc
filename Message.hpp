#ifndef MESSAGE_HPP
# define MESSAGE_HPP

#include <iostream>
#include <vector>
#include "srcs/utils.hpp"

class Message {
	private:
		std::vector<int> _targets;
		unsigned int _code;
		std::string _prefix;
		std::string _content;

	public:
		Message();
		Message(std::vector<int> targets, unsigned int code, const std::string& content);
		Message(std::vector<int> targets, const std::string& prefix, const std::string& content);
		~Message();

		const std::string getMessage() const;
		const std::vector<int> getTargets() const;
};

#endif