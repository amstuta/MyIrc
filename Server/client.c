/*
** client.c for client in /home/amstuta/rendu/PSU_2014_myirc/Server
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Fri Mar 27 15:32:10 2015 arthur
** Last update Wed Apr  8 16:54:07 2015 elkaim raphael
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "server.h"

void			accept_client(int fd)
{
  int			cs;
  struct sockaddr_in	sin_c;
  int			c_len;

  c_len = sizeof(sin_c);
  cs = accept(fd, (struct sockaddr*)&sin_c, (socklen_t*)&c_len);
  if (cs == -1)
    return ;
  write(1, "Client successfully connected\n", 30);
  add_client(cs, "");
}

int			get_user_fd(char *user)
{
  t_client		*tmp;

  tmp = g_clients;
  while (tmp)
    {
      if (!strcmp(tmp->login, user))
	return (tmp->fd);
      tmp = tmp->next;
    }
  return (0);
}

char			*get_login_from_fd(int fd)
{
  t_client		*tmp;

  tmp = g_clients;
  while (tmp)
    {
      if (tmp->fd == fd)
	return (tmp->login);
      tmp = tmp->next;
    }
  return (NULL);
}

void			add_client(int fd, char *login)
{
  t_client		*new;
  t_client		*tmp;

  if (!(new = malloc(sizeof(t_client))))
    return ;
  new->fd = fd;
  strcpy(new->login, "");
  strncat(new->login, login, 255);
  new->channel = NULL;
  new->next = NULL;
  new->cmd_in = NULL;
  strcpy(new->curbuff, "");
  new->registered = 0;
  strcpy(new->rname, "");
  if (g_clients == NULL)
    g_clients = new;
  else
    {
      tmp = g_clients;
      while (tmp->next)
	tmp = tmp->next;
      tmp->next = new;
    }
}

void			remove_client(int fd)
{
  t_client		*tmp;
  t_client		*save;

  save = NULL;
  tmp = g_clients;
  while (tmp && tmp->fd != fd)
    {
      save = tmp;
      tmp = tmp->next;
    }
  if (tmp == NULL)
    return ;
  if (save == NULL)
    g_clients = tmp->next;
  else
    save->next = tmp->next;
  free(tmp);
}
