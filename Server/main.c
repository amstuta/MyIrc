/*
** main.c for server in /home/amstuta/rendu/PSU_2014_myirc/Server
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Fri Mar 27 13:08:12 2015 arthur
** Last update Fri Mar 27 16:01:40 2015 arthur
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

void			accept_clients(int fd, int cs, int port)
{
  struct sockaddr_in	sin_c;
  int			c_len;

  (void)port;
  c_len = sizeof(sin_c);
  while (1)
    {
      cs = accept(fd, (struct sockaddr*)&sin_c, (socklen_t*)&c_len);
      if (cs == -1)
	return ;
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
  accept_clients(fd, cs, port);
}

int			main(int ac, char **av)
{
  if (ac != 2)
    {
      printf("Usage: ./server port\n");
      return (EXIT_FAILURE);
    }
  create_socket(atoi(av[1]));
  return (EXIT_SUCCESS);
}
