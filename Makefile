NAME = ircserv
CXX = c++
CXXFLAGS = -g -Wall -Wextra -Werror -std=c++98 #-fsanitize=address

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
		commands/Nick.cpp \
		commands/Ping.cpp \
		Server.cpp \
		Client.cpp \
		Channel.cpp \
		Message.cpp \
		srcs/utils.cpp \
		srcs/parse.cpp

MAIN_SRC = srcs/client_socket.cpp \
			srcs/server_socket.cpp \
			srcs/validate_args.cpp \
			srcs/main.cpp
MAIN_OBJ = $(MAIN_SRC:.cpp=.o)

TEST_SRC = testCommand.cpp
TEST_OBJ = $(TEST_SRC:.cpp=.o)
    
OBJS=$(SRCS:.cpp=.o)

CLT_SRC	=	client_test.cpp
CLT_OBJ =	$(CLT_SRC:.cpp=.o)


all: $(NAME)

$(NAME): $(OBJS) $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS) $(MAIN_OBJ)

test: $(TEST_OBJ) $(OBJS)
	$(CXX) $(CXXFLAGS) -o test $(TEST_OBJ) $(OBJS)

clt:
	$(CXX) $(CXXFLAGS) -o client $(CLT_SRC)

clean:
	rm -f $(OBJS) $(CLT_OBJ) $(MAIN_OBJ) $(TEST_OBJ)

fclean: clean
	rm -f $(NAME) client

re:
	make fclean
	make all

.PHONY: all clean fclean re