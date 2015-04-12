/*
** socket.c for socket in /home/amstuta/rendu/PSU_2014_myirc/Client
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Fri Mar 27 16:17:26 2015 arthur
** Last update Mon Apr  6 16:16:24 2015 arthur
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "client.h"

int			create_socket(char *ip, int port)
{
  int			fd;
  struct protoent	*pe;
  struct sockaddr_in	sin;

  pe = getprotobyname("TCP");
  if ((fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    {
      perror("");
      return (-1);
    }
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = inet_addr(ip);
  if (connect(fd, (const struct sockaddr*)&sin, sizeof(sin)) == -1)
    {
      perror("");
      close(fd);
      return (-1);
    }
  return (fd);
}

void			send_nick(int fd)
{
  char			buff[4096];
  char			buff2[4096];
  int			rt;

  write(1, "enter your nickname of choice:", 30);
  if ((rt = read(0, buff, 4095)) <= 0)
    exit(EXIT_FAILURE);
  buff[rt] = 0;
  send_msg(fd, strcat(strcpy(buff2, "NICK "), buff));
  send_msg(fd, "USER usr 0 *:user user");
}

int			connect_to_serv(char *cmd)
{
  int			fd;
  char			*ip;
  char			*tmp;
  int			port;

  strtok(cmd, " ");
  ip = strtok(NULL, ":");
  if (!(tmp = strtok(NULL, "")))
    return (-1);
  port = atoi(tmp);
  if (!ip || !port)
    {
      write(1, "Ip or port not specified", 24);
      return (-1);
    }
  if ((fd = create_socket(ip, port)) == -1)
    return (-1);
  printf("connected: port: %d ip: %s \n", port, ip);
  send_nick(fd);
  return (fd);
}
