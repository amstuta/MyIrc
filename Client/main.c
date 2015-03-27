/*
** main.c for client in /home/amstuta/rendu/PSU_2014_myirc/Client
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Fri Mar 27 13:07:57 2015 arthur
** Last update Fri Mar 27 16:00:38 2015 arthur
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>

int			create_socket(char *ip, int port)
{
  int			fd;
  struct protoent	*pe;
  struct sockaddr_in	sin;

  pe = getprotobyname("TCP");
  if ((fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    {
      perror("");
      exit(EXIT_FAILURE);
    }
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = inet_addr(ip);
  if (connect(fd, (const struct sockaddr*)&sin, sizeof(sin)) == -1)
    {
      perror("");
      close(fd);
      exit(EXIT_FAILURE);
    }
  return (fd);
}

int			main(int ac, char **av)
{
  int			fd;
  
  if (ac != 3)
    {
      printf("Usage: ./client ip port\n");
      return (EXIT_FAILURE);
    }
  fd = create_socket(av[1], atoi(av[2]));
  (void)fd;
  return (EXIT_SUCCESS);
}
