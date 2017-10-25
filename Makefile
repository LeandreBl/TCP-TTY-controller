##
## Makefile for *** in /home/leandre/***
## 
## Made by Léandre Blanchard
## Login   <leandre.blanchard@epitech.eu>
## 
## Started on  Thu Dec 15 20:24:11 2016 Léandre Blanchard
## Last update Mon Jul 24 21:48:02 2017 Léandre Blanchard
##

NAME	= remote-tty

CC	= gcc

LIB	= -L./lib/C -lmy
LIB	+= -lpthread

SRCS	= src/main.c
SRCS	+= src/session.c
SRCS	+= src/start_communication.c

OBJ	= $(SRCS:.c=.o)

RM	= rm -f

CFLAGS	+= -W -Werror -g3 -Wall -Wextra -I ./include

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CFLAGS) $(LIB)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
