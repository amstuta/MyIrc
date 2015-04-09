/*
** main.c for server in /home/amstuta/rendu/PSU_2014_myirc/Server
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Fri Mar 27 13:08:12 2015 arthur
** Last update Wed Apr  8 16:51:21 2015 elkaim raphael
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

t_client		*g_clients;
t_channel		*g_channels;

int			read_client(t_client *cli)
{
  int			rd;
  char			buf[4096];

  if ((rd = read(cli->fd, buf, 4095)) <= 0)
    {
      write(1, "Invalid read\n", 15);
      return (1);
    }
  buf[rd] = 0;
  command_to_list(buf, &cli->cmd_in);
  write(1, buf, strlen(buf));
  write(1, "\n", 1);
  exec_cmd(cli);
  return (0);
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
  (void)sig;
  g_clients = g_clients->next;
  while (g_clients)
    {
      write(g_clients->fd, "Server closed connection", 24);
      close(g_clients->fd);
      g_clients = g_clients->next;
    }
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
