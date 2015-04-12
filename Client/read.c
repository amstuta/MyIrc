/*
** read.c for read in /home/amstuta/rendu/PSU_2014_myirc/Client
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Fri Mar 27 16:03:33 2015 arthur
** Last update Sun Apr 12 21:58:41 2015 elkaim raphael
*/

#include <sys/select.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "client.h"

int		read_cmd_std(int fd)
{
  int		rd;
  char		buf[LINE_SIZE];
  char		line[LINE_SIZE];

  memset(line, 0, LINE_SIZE);
  if ((rd = read(0, buf, LINE_SIZE - 1)) <= 0)
    return (1);
  buf[rd - 1] = 0;
  exec_cmd(buf, fd);
  return (0);
}

int		read_cmd_serv(int fd)
{
  int		rd;
  char		buf[4096];

  if ((rd = read(fd, buf, 4095)) <= 0)
    return (1);
  buf[rd] = 0;
  exec_cmd_srv(buf);
  return (0);
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
	if (read_cmd_std(fd) == 1)
	  exit(EXIT_SUCCESS);
      if (FD_ISSET(fd, &readfds))
	if (read_cmd_serv(fd) == 1)
	  exit(EXIT_SUCCESS);
    }
}

int		read_cmd_in(int *sfd)
{
  int		rd;
  char		buff[LINE_SIZE];

  while (*sfd < 2)
    {
      if ((rd = read(0, buff, LINE_SIZE - 1)) <= 0)
	return (-1);
      buff[rd] = 0;
      if (strlen(buff) > 0)
	{
	  if (!strncmp(buff, SERVER, strlen(SERVER)))
	    {
	      if ((*sfd = connect_to_serv(buff)) != -1)
		return (0);
	    }
	  else
	    write(1, "You must be connected before sending messages\n", 46);
	  write(1, " > ", 3);
	}
    }
  return (0);
}

void		read_cmd()
{
  int		sfd;

  sfd = -1;
  write(1, " > ", 3);
  if (read_cmd_in(&sfd) == -1)
    return ;
  select_entry(sfd);
}
