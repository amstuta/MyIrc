/*
** main.c for server in /home/amstuta/rendu/PSU_2014_myirc/Server
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Fri Mar 27 13:08:12 2015 arthur
** Last update Fri Mar 27 17:06:29 2015 arthur
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "server.h"

void			accept_client(int fd, t_client **clients)
{
  int			cs;
  struct sockaddr_in	sin_c;
  int			c_len;

  c_len = sizeof(sin_c);
  cs = accept(fd, (struct sockaddr*)&sin_c, (socklen_t*)&c_len);
  if (cs == -1)
    return ;
  write(1, "Client successfully connected\n", 30);
  add_client(clients, cs, "Jimmy");
}

void			set_clients(t_client **clients, fd_set *readfds)
{
  t_client		*tmp;

  tmp = *clients;
  while (tmp)
    {
      FD_SET(tmp->fd, readfds);
      tmp = tmp->next;
    }
}

t_client		*init_clients(int fd)
{
  t_client		*res;

  if (!(res = malloc(sizeof(t_client))))
    exit(EXIT_FAILURE);
  res->fd = fd;
  res->login = NULL;
  res->channel = NULL;
  res->next = NULL;
  return (res);
}

void			check_clients_fd(t_client *clients, fd_set *readfds)
{
  t_client		*tmp;

  tmp = clients;
  while (tmp)
    {
      if (FD_ISSET(tmp->fd, readfds) != 0)
	read_client(tmp->fd, clients);
      tmp = tmp->next;
    }
}

void			my_select(int fd)
{
  fd_set		readfds;
  t_client		*clients;
  int			plus_gros_fd;

  clients = init_clients(fd);
  while (1)
    {
      FD_ZERO(&readfds);
      set_clients(&clients, &readfds);
      plus_gros_fd = get_plus_gros_fd(clients);
      if (select(plus_gros_fd + 1, &readfds, NULL, NULL, NULL) == -1)
	break;
      if (FD_ISSET(fd, &readfds) != 0)
	accept_client(fd, &clients);
      check_clients_fd(clients, &readfds);
    }
}
