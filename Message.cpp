#include "Message.hpp"
#include "srcs/utils.hpp"

Message::Message() : _code(0) {}

Message::Message(std::vector<int> targets, int code, std::string content) : _targets(targets), _code(code), _content(content) {}

Message::Message(std::vector<int> targets, std::string prefix, std::string content) : _targets(targets), _code(0), _prefix(":" + prefix), _content(content) {}

Message::~Message() {
}

const std::string Message::getMessage() {
	if (_code)
		return (":ft_irc " + std::to_string(_code) + " " + _content + " " + ft::get_code_messages(_code));
	return (_prefix + " " + _content);
}
