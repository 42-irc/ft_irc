#include "utils.hpp"

namespace ft {

    std::vector<std::string> split(const std::string &str, char charset) {
        std::vector<std::string> ret;
        std::stringstream ss(str);
        std::string tmp;

        while (getline(ss, tmp, charset)) ret.push_back(tmp);
        return ret;
    }

	const std::string& get_code_messages(int &code) {
		static std::map<int, std::string> error_messages = {
			{RPL_WELCOME, CODE_001},
			{ERR_NOSUCHNICK, CODE_401},
			{ERR_NOSUCHCHANNEL, CODE_403},
			{ERR_UNKNOWNCOMMAND, CODE_421},
			{ERR_NICKNAMEINUSE, CODE_433},
			{ERR_NOTONCHANNEL, CODE_442},
			{ERR_CHANOPRIVSNEEDED, CODE_482},
			{RPL_YOUREOPER, CODE_381},
			{RPL_LIST, CODE_322},
			{RPL_LISTEND, CODE_323}
		};
		return error_messages[code];
	}
}