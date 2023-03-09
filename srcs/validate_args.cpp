#include "validate_args.hpp"

void err_exit(std::string error_msg);

int num_of_digit(int num) {
	int cnt = 1;
	while (num >= 10) {
		num /= 10;
		++cnt;
	}
	return cnt;
}

int validate_port(char *port) {
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

void validate_password(std::string password) {
	// 비어 있지 않은지
}

void validate_args(int argc, char *argv[]) {
	if (argc != 3)
		err_exit("invalid args\nTYPE FORM >> ./ircserv <port> <password>");

	char *string_port = argv[1];
	std::string password = argv[2];

	int port = validate_port(string_port);
	validate_password(password);
}
