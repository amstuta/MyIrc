/*
** main.c for server in /home/amstuta/rendu/PSU_2014_myirc/Server
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Fri Mar 27 13:08:12 2015 arthur
** Last update Fri Apr  3 12:19:29 2015 arthur
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "server.h"

int			get_bigger_fd()
{
  int			res;
  t_client		*tmp;

  res = 0;
  tmp = g_clients;
  while (tmp)
    {
      if (tmp->fd > res)
	res = tmp->fd;
      tmp = tmp->next;
    }
  return (res);
}

void			set_clients(fd_set *readfds, fd_set *writefds)
{
  t_client		*tmp;

  tmp = g_clients;
  while (tmp)
    {
      FD_SET(tmp->fd, readfds);
      FD_SET(tmp->fd, writefds);
      tmp = tmp->next;
    }
}

t_client		*init_clients(int fd)
{
  t_client		*res;

  if (!(res = malloc(sizeof(t_client))))
    exit(EXIT_FAILURE);
  res->fd = fd;
  res->login = "";
  res->channel = NULL;
  res->next = NULL;
  return (res);
}

void			my_select(int fd)
{
  fd_set		readfds;
  fd_set		writefds;
  int			bigger_fd;

  g_clients = init_clients(fd);
  while (1)
    {
      FD_ZERO(&readfds);
      FD_ZERO(&writefds);
      set_clients(&readfds, &writefds);
      bigger_fd = get_bigger_fd();
      if (select(bigger_fd + 1, &readfds, &writefds, NULL, NULL) == -1)
	break;
      if (FD_ISSET(fd, &readfds) != 0)
	accept_client(fd);
      check_clients_fd_in(&readfds);
      check_clients_fd_out(&writefds);
    }
}
