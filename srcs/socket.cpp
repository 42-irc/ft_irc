#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/event.h>

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

	if (listen(server_socket, 5) == -1)
		err_exit("socket listening : " + std::string(strerror(errno)));

	if (fcntl(server_socket, F_SETFL, O_NONBLOCK) == -1)
		err_exit("setting socket flag : " + std::string(strerror(errno)));

	int kq = kqueue();
	if (kq == -1)
		err_exit("creating kqueue : " + std::string(strerror(errno)));

	struct kevent events[2];
	EV_SET(&events[0], server_socket, EVFILT_READ, EV_ADD, 0, 0, NULL);

	std::cout << "Waiting for incoming connections..." << std::endl;
	{
		int nev = kevent(kq, events, 1, events, 2, NULL);
		if (nev == -1)
			err_exit("calling kevent : " + std::string(strerror(errno)));

		for (int i = 0; i < nev; ++i)
		{
			// 서버 소켓에 READ 이벤트 발생 시
			if (events[i].ident == server_socket)
			{
				std::cout << "READ event occurs in server_socket!" << std::endl;

				int client_socket = accept(server_socket, NULL, NULL);
				if (client_socket == -1)
					err_exit("accepting client : " + std::string(strerror(errno)));

				std::cout << client_socket << ": New client connected" << std::endl;

				if (fcntl(client_socket, F_SETFL, O_NONBLOCK) == -1)
					err_exit("setting client socket flag : " + std::string(strerror(errno)));

				EV_SET(&events[1], client_socket, EVFILT_READ, EV_ADD, 0, 0, NULL);
			}
			else
			{
				// 클라이언트 소켓에 read 이벤트 발생 시
			}
		}
	}
}
