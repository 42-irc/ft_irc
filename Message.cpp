#include "Message.hpp"
#include "srcs/utils.hpp"

Message::Message(): _code(0) {
}

Message::Message(std::vector<int> targets, int code, std::string prefix, std::string command, std::string params) : _targets(targets), _code(code), _prefix(prefix), _command(command), _params(params) {
}

Message::~Message() {
}

const std::string Message::getMessage() {
	if (_code != 0)
		return (":" + _prefix + " ERROR " + std::to_string(_code) + " " + ft::get_code_messages(_code));
	return (":" + _prefix + " " + _command + " " + _params);
}
