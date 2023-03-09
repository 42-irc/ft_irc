NAME = ircserv
CXX = c++
CXXFLAGS = -g#-Wall -Wextra -Werror -std=c++98
SRCS =	commands/Command.cpp \
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
		commands/User.cpp \
		srcs/client_socket.cpp srcs/server_socket.cpp \
		srcs/validate_args.cpp \
		srcs/main.cpp \
		# testCommand.cpp

CLT_SRC	=	client_test.cpp
CLT_OBJ =	$(CLT_SRC:.cpp=.o)

OBJS=$(SRCS:.cpp=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

clt:
	$(CXX) $(CXXFLAGS) -o client $(CLT_SRC)

clean:
	rm -f $(OBJS) $(CLT_OBJ)

fclean: clean
	rm -f $(NAME) client

re:
	make fclean
	make all

.PHONY: all clean fclean re