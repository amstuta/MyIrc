##
## Makefile for myirc in /home/amstuta/rendu/PSU_2014_myirc
##
## Made by arthur
## Login   <amstuta@epitech.net>
##
## Started on  Fri Mar 27 12:59:11 2015 arthur
## Last update Wed Apr  8 14:01:38 2015 elkaim raphael
##

RM	= rm -f

CC	= gcc

CFLAGS	= -Wall -Wextra -Werror

NAME	= client
NAME2	= server

SRCS_C	= Client/main.c \
	  Client/read.c \
	  Client/socket.c \
	  Client/cmd.c
SRCS_S	= Server/main.c \
	  Server/client.c \
	  Server/select.c \
	  Server/channels.c \
	  Server/exec.c \
	  Server/cmds.c \
	  Server/cmds2.c \
	  Server/io.c \
	  Server/circ_buff.c \
	  Server/parse.c \
	  Server/msg.c \
	  Server/check.c \
	  Server/chan_list.c

OBJS_C	= $(SRCS_C:.c=.o)
OBJS_S	= $(SRCS_S:.c=.o)

all: $(NAME) $(NAME2)

$(NAME):$(OBJS_C)
	 $(CC) $(OBJS_C) -o $(NAME)

$(NAME2):$(OBJS_S)
	 $(CC) $(OBJS_S) -o $(NAME2)

clean:
	 $(RM) $(OBJS_C) $(OBJS_S)

fclean:	 clean
	 $(RM) $(NAME) $(NAME2)

re:	 fclean all

.PHONY:	 all clean fclean re
