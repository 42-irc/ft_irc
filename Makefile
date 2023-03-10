NAME = ircserv
CXX = c++
CXXFLAGS = -g -Wall -Wextra -Werror -std=c++98

SRCS =	commands/Command.cpp \
		commands/Join.cpp \
		commands/PrivMsg.cpp \
		commands/Kick.cpp \
		commands/List.cpp \
		commands/Oper.cpp \
		commands/Part.cpp \
		commands/Pass.cpp \
		commands/User.cpp \
		commands/Quit.cpp \
		Server.cpp \
		Client.cpp \
		Channel.cpp \
		Message.cpp \
		srcs/utils.cpp \
		srcs/parse.cpp \
		srcs/client_socket.cpp \
		srcs/server_socket.cpp \
		srcs/validate_args.cpp \
		srcs/main.cpp
		# testCommand.cpp
    
OBJS=$(SRCS:.cpp=.o)

CLT_SRC	=	client_test.cpp
CLT_OBJ =	$(CLT_SRC:.cpp=.o)


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