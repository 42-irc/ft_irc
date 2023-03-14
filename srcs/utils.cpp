#include "utils.hpp"
#include "ircserv.hpp"

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

	time_t getSecondDiff(time_t lastPingTime) {
		time_t currentTime = time(NULL);
		return (currentTime - lastPingTime);
	}

	bool isClosed(int socketFd) {
		char buffer[1024];
		memset(buffer, 0, sizeof(buffer));
		ssize_t n = recv(socketFd, buffer, sizeof(buffer), 0);
		return (n == 0);
	}

	unsigned long num_of_digit(int num) {
		unsigned long cnt = 1;
		while (num >= 10) {
			num /= 10;
			++cnt;
		}
		return cnt;
	}

	int validate_port(char* port) {
		int port_num = atoi(port);

		// 숫자만으로 구성되는지 확인
		if ((port_num == 0 && (strlen(port) != 1 || port[0] != '0'))
			|| (strlen(port) != num_of_digit(port_num)))
			err_exit("invalid port");

		// port 번호 범위 0 ~ 65535
		if (port_num < 0 || port_num > 65535)
			err_exit("invalid port");
		return port_num;
	}

	inline std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v") {
		s.erase(0, s.find_first_not_of(t));
		return s;
	}

	inline std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v") {
		s.erase(s.find_last_not_of(t) + 1);
		return s;
	}

	inline std::string& trim(std::string& s, const char* t = " \t\n\r\f\v") {
		return ltrim(rtrim(s, t), t);
	}

	void validate_password(std::string password) {
		// 비어 있지 않은지
		if (trim(password).empty())
			err_exit("invalid password");
	}

	int validate_args(int argc, char *argv[]) {
		if (argc != 3)
			err_exit("invalid args\nTYPE FORM >> ./ircserv <port> <password>");

		char *string_port = argv[1];
		std::string password = argv[2];

		int port = validate_port(string_port);
		validate_password(password);

		return port;
	}

}