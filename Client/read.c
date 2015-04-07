/*
** read.c for read in /home/amstuta/rendu/PSU_2014_myirc/Client
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Fri Mar 27 16:03:33 2015 arthur
** Last update Tue Apr  7 13:30:26 2015 arthur
*/

#include <term.h>
#include <curses.h>
#include <sys/select.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "client.h"

void		read_cmd_std(int fd)
{
  int		rd;
  char		buf[LINE_SIZE];
  char		line[LINE_SIZE];

  memset(line, 0, LINE_SIZE);
  while (1)
    {
      if ((rd = read(0, buf, LINE_SIZE - 1)) <= 0)
	return ;
      buf[rd] = 0;
      if (strlen(buf) > 0 && buf[0] == 10)
	break ;
      else
	{
	  strcat(line, buf);
	  write(1, buf, strlen(buf));
	  memset(buf, 0, LINE_SIZE);
	}
    }
  /*if (!check_cmd(buf))
    return ;*/
  write(fd, line, strlen(line));
  write(1, "\n", 1);
}

void		read_cmd_serv(int fd)
{
  int		rd;
  char		buf[4096];

  if ((rd = read(fd, buf, 4095)) <= 0)
    return ;
  buf[rd] = 0;
  write(1, "\x1b[34m", 7);
  write(1, buf, strlen(buf));
  write(1, "\x1b[0m", 6);
  write(1, "\n", 1);
}

void		select_entry(int fd)
{
  fd_set	readfds;

  while (1)
    {
      write(1, " > ", 3);
      FD_ZERO(&readfds);
      FD_SET(0, &readfds);
      FD_SET(fd, &readfds);
      if (select(fd + 1, &readfds, NULL, NULL, NULL) == -1)
	return ;
      if (FD_ISSET(0, &readfds))
	read_cmd_std(fd);
      if (FD_ISSET(fd, &readfds))
	read_cmd_serv(fd);
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
  char		buf[LINE_SIZE];

  sfd = -1;
  write(1, " > ", 3);
  if (read_cmd_in(&sfd) == -1)
    return ;
  if (!tgetent(buf, getenv("TERM")))
    return ;
  if ((clr = tgetstr("cl", NULL)) != NULL)
    write(1, clr, strlen(clr));
  select_entry(sfd);
}
