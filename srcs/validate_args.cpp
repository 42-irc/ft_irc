#include "validate_args.hpp"
#include "main.hpp"

void err_exit(std::string error_msg);

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
