##
## EPITECH PROJECT, 2017
## lbl-libc
## File description:
## makefile
##

NAME	= libmy.a

CC	= gcc

MAKE	= make -C

SRCS	= libcatalloc.a
SRCS	+= libdefault.a
SRCS	+= libgetlineshell.a
SRCS	+= libgnl.a
SRCS	+= libprintf.a

RM	= rm -f

all: $(NAME)

$(NAME):
	$(MAKE) catalloc
	$(MAKE) printf
	$(MAKE) default
	$(MAKE) getline_shell
	$(MAKE) get_next_line
	ar -rcT $(NAME) $(SRCS)
clean:
	$(MAKE) catalloc clean
	$(MAKE) printf clean
	$(MAKE) default clean
	$(MAKE) getline_shell clean
	$(MAKE) get_next_line clean
	$(RM) $(SRCS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
