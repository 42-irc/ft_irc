#include "utils.hpp"

namespace ft {

    std::vector<std::string> split(const std::string &str, char charset) {
        std::vector<std::string> ret;
        std::stringstream ss(str);
        std::string tmp;

        while (getline(ss, tmp, charset)) ret.push_back(tmp);
        return ret;
    }

	const std::string get_code_messages(int &code) {
		switch (code)
		{
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
			default:
				return "";
		}
	}
}