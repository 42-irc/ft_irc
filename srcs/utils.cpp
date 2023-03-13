#include "utils.hpp"

namespace ft
{

    std::vector<std::string> split(const std::string& str, char charset, unsigned long n) {
        std::vector<std::string> ret;
        std::stringstream ss(str);
        std::string tmp;
		unsigned long i = 0;

		if (n) {
			while (++i < n && getline(ss, tmp, charset))
				ret.push_back(tmp);
			if (i == n && getline(ss, tmp, '\0'))
				ret.push_back(tmp);
			while (ret.size() < n)
				ret.push_back("");
		} else {
			while (getline(ss, tmp, charset))
				ret.push_back(tmp);
		}
        return ret;
    }

	// split a string with multiple charsets
	std::vector<std::string> split(const std::string& str, const std::string charset) {
		std::vector<std::string> ret;
		std::string tmp = str;

		while (tmp.size()) {
			std::size_t idx = tmp.find_first_of(charset);
			if (idx)
				ret.push_back(tmp.substr(0, idx));
			tmp.erase(0, idx);
			idx = tmp.find_first_not_of(charset);
			tmp.erase(0, idx);
		}
		return ret;
	}

	const std::string getCodeMessage(int code) {
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

	const std::string codeToString(unsigned int n) {
		std::stringstream ss;
		if (n < 10)
			ss << "00";
		else if (n < 100)
			ss << "0";
		ss << n;
		return ss.str();
	}

	time_t getSecondDiff(time_t lastPingTime) {
		time_t currentTime = time(NULL);
		return (currentTime - lastPingTime);
	}

}