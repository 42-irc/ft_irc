NAME = test
CXX = c++
# CXXFLAGS = #-Wall -Wextra -Werror -std=c++98
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
		commands/Quit.cpp

OBJS=$(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:
	make fclean
	make all

.PHONY: all clean fclean re