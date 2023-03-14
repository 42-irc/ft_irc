#include "Message.hpp"

Message::Message() : _code(0) {}

Message::Message(std::vector<int> targets, unsigned int code, const std::string& content) : _targets(targets), _code(code), _content(content) {}

Message::Message(std::vector<int> targets, const std::string& prefix, const std::string& content) : _targets(targets), _code(0), _prefix(":" + prefix), _content(content) {}

Message::~Message() {}

const std::string Message::getMessage() {
	if (_code)
		return (":ft_irc " + codeToString(_code) + " " + _content + " " + getCodeMessage(_code) + "\r\n");
	if (_prefix.empty())
		return (_content  + "\r\n");
	return (_prefix + " " + _content + "\r\n");
}

std::vector<int> Message::getTargets() { return _targets; }

void Message::sendMessage() {
	std::string message = getMessage();
	for (std::vector<int>::iterator it = _targets.begin(); it != _targets.end(); it++) {
		send(*it, message.c_str(), message.size(), 0);
	}
}

const std::string Message::getCodeMessage(int code) {
	switch (code) {
		case RPL_WELCOME:
			return CODE_001;
		case ERR_NOSUCHNICK:
			return CODE_401;
		case ERR_NOSUCHCHANNEL:
			return CODE_403;
		case ERR_UNKNOWNCOMMAND:
			return CODE_421;
		case ERR_NICKNAMEINUSE:
			return CODE_433;
		case ERR_NOTONCHANNEL:
			return CODE_442;
		case ERR_CHANOPRIVSNEEDED:
			return CODE_482;
		case RPL_LIST:
			return CODE_322;
		case RPL_LISTEND:
			return CODE_323;
		case RPL_YOUREOPER:
			return CODE_381;
		case ERR_NEEDMOREPARAMS:
			return CODE_461;
		case ERR_PASSWDMISMATCH:
			return CODE_464;
		default:
			return "";
	}
}

const std::string Message::codeToString(unsigned int n) {
	std::stringstream ss;
	if (n < 10)
		ss << "00";
	else if (n < 100)
		ss << "0";
	ss << n;
	return ss.str();
}
