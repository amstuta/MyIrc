/*
** main.c for server in /home/amstuta/rendu/PSU_2014_myirc/Server
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Fri Mar 27 13:08:12 2015 arthur
** Last update Fri Mar 27 17:06:29 2015 arthur
*/

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "server.h"

void			accept_clients(int fd)
{
  int			cs;
  struct sockaddr_in	sin_c;
  int			c_len;

  c_len = sizeof(sin_c);
  while (1)
    {
      cs = accept(fd, (struct sockaddr*)&sin_c, (socklen_t*)&c_len);
      if (cs == -1)
	return ;
    }
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

int			get_plus_gros_fd(t_client *clients)
{
  int			res;
  t_client		*tmp;

  res = 0;
  tmp = clients;
  while (tmp)
    {
      if (tmp->fd > res)
	res = tmp->fd;
      tmp = tmp->next;
    }
  return (res);
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
    }
}

void			create_socket(int port)
{
  int			cs;
  int			fd;
  struct protoent	*pe;
  struct sockaddr_in	sin;

  pe = getprotobyname("TCP");
  if ((fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return ;
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = INADDR_ANY;
  if (bind(fd, (const struct sockaddr*)&sin, sizeof(sin)) == -1)
    {
      close(fd);
      return ;
    }
  if ((cs = listen(fd, 1)) == -1)
    {
      close(fd);
      return ;
    }
  my_select(fd);
  //accept_clients(fd,/*, cs */ port);
}

void			exit_signal(int sig)
{
  // Envoi msg a tous les fds
  // Close tous les fds
  (void)sig;
  write(1, "Exiting...", 11);
  exit(EXIT_SUCCESS);
}

int			main(int ac, char **av)
{
  if (ac != 2)
    {
      printf("Usage: ./server port\n");
      return (EXIT_FAILURE);
    }
  signal(SIGINT, exit_signal);
  create_socket(atoi(av[1]));
  return (EXIT_SUCCESS);
}
