NAME = ircserv
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -Isrcs -Isrcs/command -Isrcs/channel -Isrcs/message -Isrcs/client -Isrcs/server #-g #-fsanitize=address

SRCDIR=srcs
CMDDIR=srcs/command

CMD_SRCS = $(CMDDIR)/Command.cpp \
		$(CMDDIR)/Join.cpp \
		$(CMDDIR)/PrivMsg.cpp \
		$(CMDDIR)/Kick.cpp \
		$(CMDDIR)/List.cpp \
		$(CMDDIR)/Oper.cpp \
		$(CMDDIR)/Part.cpp \
		$(CMDDIR)/Pass.cpp \
		$(CMDDIR)/User.cpp \
		$(CMDDIR)/Quit.cpp \
		$(CMDDIR)/Nick.cpp \
		$(CMDDIR)/Notice.cpp \
		$(CMDDIR)/Ping.cpp

UTIL_SRCS = $(SRCDIR)/utils.cpp \
			$(SRCDIR)/parse.cpp

MAIN_SRCS = $(SRCDIR)/server/Server.cpp \
			$(SRCDIR)/client/Client.cpp \
			$(SRCDIR)/channel/Channel.cpp \
			$(SRCDIR)/message/Message.cpp \
			$(SRCDIR)/client_socket.cpp \
			$(SRCDIR)/server_socket.cpp \
			$(SRCDIR)/main.cpp

CMD_OBJS=$(CMD_SRCS:.cpp=.o)
UTIL_OBJS=$(UTIL_SRCS:.cpp=.o)
MAIN_OBJS=$(MAIN_SRCS:.cpp=.o)

SRCS=$(CMD_SRCS) $(MAIN_SRCS) $(UTIL_SRCS)
OBJS=$(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(MAIN_OBJS) $(CMD_OBJS) $(UTIL_OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(MAIN_OBJS) $(CMD_OBJS) $(UTIL_OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) client

re:
	make fclean
	make all

.PHONY: all clean fclean re