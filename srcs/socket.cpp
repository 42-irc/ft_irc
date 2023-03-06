#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
	int server_socket;
	struct sockaddr_in server_addr;

	server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server_socket == -1)
	{
		std::cerr << "Error creating socket: " << strerror(errno) << std::endl;
		return 1;
	}

	std::cout << "Connected to server" << std::endl;
	return 0;
}