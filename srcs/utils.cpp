#include "utils.hpp"

namespace ft {

std::vector<std::string> split(const std::string &str, char charset) {
	std::vector<std::string> ret;
    std::stringstream ss(str);
    std::string tmp;

    while (getline(ss, tmp, charset)) ret.push_back(tmp);
    return ret;
}

}