/*
** read.c for read in /home/amstuta/rendu/PSU_2014_myirc/Client
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Fri Mar 27 16:03:33 2015 arthur
** Last update Fri Mar 27 16:59:10 2015 arthur
*/

#include <sys/select.h>
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

void		read_cmd()
{
  int		rd;
  int		sfd;
  char		buff[LINE_SIZE];

  sfd = -1;
  while (sfd < 2)
    {
      if ((rd = read(0, buff, LINE_SIZE - 1)) <= 0)
	return ;
      buff[rd] = 0;
      if (!strncmp(buff, SERVER, strlen(SERVER)))
	sfd = connect_to_serv(buff);
      else
	write(1, "Error: unknown command\n", 23);
    }
  select_entry(sfd);
}
