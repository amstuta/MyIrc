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

void			read_client(int fd, t_client *clients)
{
  int			rd;
  char			buf[4096];

  if ((rd = read(fd, buf, 4095)) == -1)
    return ;
  buf[rd] = 0;

  t_client *tmp = clients->next;
  while (tmp)
    {
      if (tmp->fd != fd)
	write(tmp->fd, buf, strlen(buf));
      tmp = tmp->next;
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
