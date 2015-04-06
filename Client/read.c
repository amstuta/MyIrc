/*
** read.c for read in /home/amstuta/rendu/PSU_2014_myirc/Client
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Fri Mar 27 16:03:33 2015 arthur
** Last update Mon Apr  6 16:39:26 2015 arthur
*/

#include <term.h>
#include <curses.h>
#include <sys/select.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "client.h"

void		read_cmd_std(int fd)
{
  int		rd;
  char		buf[4096];

  if ((rd = read(0, buf, 4095)) <= 0)
    return ;
  buf[rd] = 0;
  if (!check_cmd(buf))
    return ;
  write(fd, buf, strlen(buf));
}

void		read_cmd_serv(int fd)
{
  int		rd;
  char		buf[4096];

  if ((rd = read(fd, buf, 4095)) <= 0)
    return ;
  buf[rd] = 0;
  write(1, buf, strlen(buf));
  write(1, "\n", 1);
}

void		select_entry(int fd)
{
  fd_set	readfds;

  while (1)
    {
      FD_ZERO(&readfds);
      FD_SET(0, &readfds);
      FD_SET(fd, &readfds);
      if (select(fd + 1, &readfds, NULL, NULL, NULL) == -1)
	return ;
      if (FD_ISSET(0, &readfds))
	{
	  read_cmd_std(fd);
	}
      if (FD_ISSET(fd, &readfds))
	{
	  read_cmd_serv(fd);
	}
    }
}

int		read_cmd_in(int *sfd)
{
  int		rd;
  char		buff[LINE_SIZE];
  char		line[LINE_SIZE];

  while (*sfd < 2)
    {
      if ((rd = read(0, buff, LINE_SIZE - 1)) <= 0)
	return (-1);
      buff[rd] = 0;
      if (strlen(buff) > 0 && buff[0] == 10)
	{
	  if (!strncmp(line, SERVER, strlen(SERVER)))
	    *sfd = connect_to_serv(line);
	  else
	    write(1, "You must be connected before sending messages\n", 46);
	  memset(line, 0, LINE_SIZE);
	  write(1, " > ", 3);
	}
      else
	{
	  strcat(line, buff);
	  write(1, buff, strlen(buff));
	}
    }
  return (0);
}

void		read_cmd()
{
  int		sfd;
  char		*clr;

  sfd = -1;
  write(1, " > ", 3);
  if (read_cmd_in(&sfd) == -1)
    return ;
  /*if ((clr = tgetstr("clear", NULL)) != NULL)
    write(1, clr, strlen(clr));*/
  // Clear ecran
  select_entry(sfd);
}
