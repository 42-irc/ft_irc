#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/event.h>
#include <vector>
#include <unistd.h>

void err_exit(std::string error_msg) {
	std::cerr << "Error " << error_msg << std::endl;
	exit(1);
}

int main() {
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

	struct kevent server_socket_event;
	EV_SET(&server_socket_event, server_socket, EVFILT_READ, EV_ADD, 0, 0, NULL);
	kevent(kq, &server_socket_event, 1, NULL, 0, NULL);

	while (true) {
		std::cout << "Waiting for events..." << std::endl;

		struct kevent occurred_events[100];
		int occured_events_cnt = kevent(kq, NULL, 0, occurred_events, 100, NULL);
		if (occured_events_cnt == -1)
			err_exit("calling kevent : " + std::string(strerror(errno)));

		std::cout << occured_events_cnt << " events occur!" << std::endl;

		for (int i = 0; i < occured_events_cnt; ++i) {
			// 이벤트가 발생한 식별자가 서버 소켓의 fd인 경우
			if (occurred_events[i].ident == server_socket) {
				int client_socket = accept(server_socket, NULL, NULL);
				if (client_socket == -1)
					err_exit("accepting client : " + std::string(strerror(errno)));

				std::cout << client_socket << ": New client connected\n" << std::endl;

				if (fcntl(client_socket, F_SETFL, O_NONBLOCK) == -1)
					err_exit("setting client socket flag : " + std::string(strerror(errno)));

				struct kevent client_socket_event[2];
				EV_SET(&client_socket_event[0], client_socket, EVFILT_READ, EV_ADD, 0, 0, NULL);
				EV_SET(&client_socket_event[1], client_socket, EVFILT_WRITE, EV_ADD, 0, 0, NULL);
				kevent(kq, &client_socket_event[0], 2, NULL, 0, NULL);
			}
			// 이벤트가 발생한 식별자가 클라이언트 소켓의 fd인 경우
			else {
				// READ 이벤트 발생
				if (occurred_events[i].filter == EVFILT_READ) {
					char buffer[1024];
					ssize_t n = recv(occurred_events[i].ident, buffer, sizeof(buffer), 0);
					if (n < 0) {
						err_exit("receiving from client socket : " + std::string(strerror(errno)));
					} else if (n == 0) {
						std::cout << occurred_events[i].ident << " Client closed connection\n" << std::endl;
						close(occurred_events[i].ident);
					} else {
						// 클라이언트 메시지 수신 성공
						std::cout << buffer << std::endl;
					}
				// WRITE 이벤트 발생
				} else {
				}
			}
		}
	}
}