#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/event.h>
#include <vector>

void err_exit(std::string error_msg)
{
	std::cerr << "Error " << error_msg << std::endl;
	exit(1);
}

void initialize_new_event(std::vector<struct kevent> event_list,
						  uintptr_t sock_fd, int16_t filter, uint16_t flags)
{
	struct kevent new_event;
	EV_SET(&new_event, sock_fd, filter, flags, 0, 0, NULL);
	event_list.push_back(new_event);
}

int main()
{
	int server_socket;
	struct sockaddr_in server_addr;

	server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server_socket == -1)
		err_exit("creating server socket : " + std::string(strerror(errno)));

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	server_addr.sin_port = htons(8080);

	if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
		err_exit("binding server socket : " + std::string(strerror(errno)));

	if (listen(server_socket, 5) == -1)
		err_exit("server socket listening : " + std::string(strerror(errno)));

	if (fcntl(server_socket, F_SETFL, O_NONBLOCK) == -1)
		err_exit("setting server socket flag : " + std::string(strerror(errno)));

	int kq = kqueue();
	if (kq == -1)
		err_exit("creating kqueue : " + std::string(strerror(errno)));

	std::vector<struct kevent> register_events;
	initialize_new_event(register_event, server_socket, EVFILT_READ, EV_ADD);

	std::cout << "Waiting for incoming connections..." << std::endl;

	while (true)
	{
		struct kevent occured_events[2];
		int occured_events_cnt = kevent(kq, &register_events[0], register_events.size(), occured_events, 2, NULL);
		if (occured_events_cnt == -1)
			err_exit("calling kevent : " + std::string(strerror(errno)));

		std::cout << occured_events_cnt << " events occur!\n"
				  << std::endl;
		for (int i = 0; i < occured_events_cnt; ++i)
		{
			// 이벤트가 발생한 식별자가 서버 소켓의 fd인 경우
			if (occured_events[i].ident == server_socket)
			{
				std::cout << "TYPE " << register_event[i].filter << " event occurs in server_socket!" << std::endl;

				int client_socket = accept(server_socket, NULL, NULL);
				if (client_socket == -1)
					err_exit("accepting client : " + std::string(strerror(errno)));

				std::cout << client_socket << ": New client connected" << std::endl;

				if (fcntl(client_socket, F_SETFL, O_NONBLOCK) == -1)
					err_exit("setting client socket flag : " + std::string(strerror(errno)));
			}
			else
			{
				// 이벤트가 발생한 식별자가 클라이언트 소켓의 fd인 경우
				std::cout << "event occurs in client_socket!" << std::endl;
			}
		}
	}
}