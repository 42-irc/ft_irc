#include "Message.hpp"

Message::Message() {}

Message::Message(unsigned int code) : _prefix(SERVER_PREFIX), _command(codeToString(code)), _trailer(getCodeMessage(code)) {}
Message::Message(std::string prefix, std::string command) : _prefix(":" + prefix), _command(command) {}

Message::~Message() {}

const std::string Message::getMessage() {
	std::string message = "";

	if (_prefix != "")
		message += _prefix + " ";
	message += _command;
	for (std::vector<std::string>::iterator it = _params.begin(); it != _params.end(); it++)
		message += " " + *it;
	if (_trailer != "")
		message += " " + _trailer;
	message += "\r\n";
	return message;
}

void Message::sendMessage() {
	std::string message = getMessage();

	for (std::vector<int>::iterator it = _targets.begin(); it != _targets.end(); it++) {
		std::string message_copy = message;
		while (true) {
			ssize_t n = send(*it, message_copy.c_str(), message_copy.size(), 0);
			if (n == (ssize_t)message_copy.size())
				break;
			message_copy = message_copy.substr(n);
		}
		// std::cout << "Sending message to client[" << *it << "]" << std::endl;
		// std::cout << message << std::endl;
	}
}

void Message::addTarget(int target) {
	_targets.push_back(target);
}

void Message::addTargets(std::vector<int> targets) {
	_targets.insert(_targets.end(), targets.begin(), targets.end());
}

void Message::addParam(std::string param) {
	_params.push_back(param);
}

void Message::addParams(std::vector<std::string> params) {
	_params.insert(_params.end(), params.begin(), params.end());
}

void Message::setTrailer(std::string trailer) {
	if (trailer[0] != ':')
		_trailer = ":" + trailer;
	else
		_trailer = trailer;
}

std::vector<int> Message::getTargets() { return _targets; }

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
		case RPL_NAMREPLY:
			return CODE_353;
		case RPL_NAMEND:
			return CODE_366;
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
