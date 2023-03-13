#include "Message.hpp"
#include "srcs/utils.hpp"

Message::Message() : _code(0) {}

Message::Message(std::vector<int> targets, unsigned int code, const std::string& content) : _targets(targets), _code(code), _content(content) {}

Message::Message(std::vector<int> targets, const std::string& prefix, const std::string& content) : _targets(targets), _code(0), _prefix(":" + prefix), _content(content) {}

Message::~Message() {}

const std::string Message::getMessage() const {
	if (_code)
		return (":ft_irc " + ft::codeToString(_code) + " " + _content + " " + ft::getCodeMessage(_code) + "\r\n");
	if (_prefix.empty())
		return (_content  + "\r\n");
	return (_prefix + " " + _content + "\r\n");
}

const std::vector<int> Message::getTargets() const { return _targets; }
