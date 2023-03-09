NAME = test
CXX = c++
CXXFLAGS = -g#-Wall -Wextra -Werror -std=c++98
SRCS = testCommand.cpp \
		commands/Command.cpp \
		commands/Join.cpp \
		commands/PrivMsg.cpp \
		commands/Kick.cpp \
		commands/List.cpp \
		commands/Oper.cpp \
		Server.cpp \
		Client.cpp \
		srcs/utils.cpp \
		Channel.cpp \
		Message.cpp \
		commands/Quit.cpp \
		commands/User.cpp

SERV_SRCS	=	srcs/main.cpp \
				srcs/client_socket.cpp srcs/server_socket.cpp \
				srcs/validate_args.cpp

SERV_OBJS=$(SERV_SRCS:.cpp=.o)

OBJS=$(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

serv: $(SERV_OBJS)
	$(CXX) $(CXXFLAGS) -o ircserv $(SERV_OBJS)

clean:
	rm -f $(OBJS) $(SERV_OBJS)

fclean: clean
	rm -f $(NAME) ircserv

re:
	make fclean
	make all

.PHONY: all clean fclean re