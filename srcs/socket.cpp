#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

void err_exit(std::string error_msg)
{
	std::cerr << "Error " << error_msg << std::endl;
	exit(1);
}

int main()
{
	int server_socket;
	struct sockaddr_in server_addr;

	server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server_socket == -1)
		err_exit("creating socket : " + std::string(strerror(errno)));

	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	server_addr.sin_port = htons(8080);

	if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
		err_exit("binding socket : " + std::string(strerror(errno)));

	if (listen(server_socket, 10) == -1)
		err_exit("socket listening : " + std::string(strerror(errno)));

	if (fcntl(server_socket, F_SETFL, O_NONBLOCK) == -1)
		err_exit("setting socket flag : " + std::string(strerror(errno)));

	std::cout << "Connected to server" << std::endl;
}