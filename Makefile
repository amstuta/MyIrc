##
## Makefile for myirc in /home/amstuta/rendu/PSU_2014_myirc
##
## Made by arthur
## Login   <amstuta@epitech.net>
##
## Started on  Fri Mar 27 12:59:11 2015 arthur
## Last update Fri Mar 27 13:07:49 2015 arthur
##

RM	= rm -f

CC	= gcc

CFLAGS	= -Wall -Wextra -Werror

NAME1	= client
NAME2	= server

SRCS_C	= Client/main.c
SRCS_S	= Server/main.c

OBJS_C	= $(SRCS_C:.c=.o)
OBJS_S	= $(SRCS_S:.c=.o)

all: $(NAME1) $(NAME2)

$(NAME1):$(OBJS_C)
	 $(CC) $(OBJS_C) -o $(NAME1)

$(NAME2):$(OBJS_S)
	 $(CC) $(OBJS_S) -o $(NAME2)

clean:
	 $(RM) $(OBJS_C) $(OBJS_S)

fclean:	 clean
	 $(RM) $(NAME1) $(NAME2)

re:	 fclean all

.PHONY:	 all clean fclean re
