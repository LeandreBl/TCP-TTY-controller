##
## Makefile for *** in /home/leandre/***
## 
## Made by Léandre Blanchard
## Login   <leandre.blanchard@epitech.eu>
## 
## Started on  Thu Dec 15 20:24:11 2016 Léandre Blanchard
## Last update Wed Oct 25 23:11:54 2017 Léandre Blanchard
##

NAME	= remote-tty

CC	= gcc

MAKE	= make -C

LIB	= -L./lib/C -lmy
LIB	+= -lpthread

SRCS	= src/main.c
SRCS	+= src/session.c
SRCS	+= src/start_communication.c
SRCS	+= src/server.c
SRCS	+= src/server_thread.c
SRCS	+= src/client.c
SRCS	+= src/client_thread.c
SRCS	+= src/receive.c
SRCS	+= src/receive_welcome.c
SRCS	+= src/send_msg.c
SRCS	+= src/receive_leave.c

OBJ	= $(SRCS:.c=.o)

RM	= rm -f

CFLAGS	+= -W -Werror -g3 -Wall -Wextra -I ./include

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) lib/C
	$(CC) $(OBJ) -o $(NAME) $(CFLAGS) $(LIB)
	@	tput setaf 2; cat include/signature; tput sgr0

clean:
	$(MAKE) lib/C clean
	$(RM) $(OBJ)

fclean: clean
	$(MAKE) lib/C fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
