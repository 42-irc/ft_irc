#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

void err_exit(std::string error_msg)
{
	std::cerr << "Error " << error_msg << std::endl;
	exit(1);
}

int main()
{
	int client_socket;
	struct sockaddr_in server_addr;

	client_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (client_socket == -1)
		err_exit("creating socket : " + std::string(strerror(errno)));

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8080);
	if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0)
		err_exit("converting server IP address");

	if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
		err_exit("connecting to server : " + std::string(strerror(errno)));

	std::cout << "Connected to server" << std::endl;

	char buffer[256];
	int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
	if (bytes_received == -1)
		err_exit("receiving data from server : " + std::string(strerror(errno)));
	else if (bytes_received == 0)
		std::cout << "Server disconnected" << std::endl;
	else
		std::cout << "Received message from server: " << buffer << std::endl;

	// 서버가 닫힐 때까지 클라이언트 유지
	while (true)
	{
		int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
		if (bytes_received == -1)
			err_exit("receiving data from server : " + std::string(strerror(errno)));
		else if (bytes_received == 0)
		{
			std::cout << "Server disconnected" << std::endl;
			break;
		}
	}

	close(client_socket);
	return 0;
}
