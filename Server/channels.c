/*
** client.c for client in /home/amstuta/rendu/PSU_2014_myirc/Server
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Fri Mar 27 15:32:10 2015 arthur
** Last update Tue Apr  7 13:39:17 2015 arthur
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "server.h"

void		add_channel(char *name)
{
  t_channel	*new;
  t_channel	*tmp;

  if (!(new = malloc(sizeof(t_channel))) || !name)
    return ;
  new->name = strdup(name);
  new->next = NULL;
  if (g_channels == NULL)
    g_channels = new;
  else
    {
      tmp = g_channels;
      while (tmp->next)
	tmp = tmp->next;
      tmp->next = new;
    }
}

int		channel_exists(char *c)
{
  t_channel	*tmp;

  tmp = g_channels;
  while (tmp)
    {
      if (tmp->name && c && !strcmp(tmp->name, c))
	return (1);
      tmp = tmp->next;
    }
  return (0);
}

char		*get_client_channel(int fd)
{
  t_client	*tmp;

  tmp = g_clients;
  while (tmp)
    {
      if (tmp->fd == fd)
	return (tmp->channel);
    }
  return (NULL);
}

void		list_channels(int fd)
{
  t_channel	*tmp;

  tmp = g_channels;
  write(fd, "Available channels:", 19);
  while (tmp)
    {
      write(fd, tmp->name, strlen(tmp->name));
      tmp = tmp->next;
    }
  write(fd, "----------", 10);
}

void		search_channels(int fd, char *s)
{
  t_channel	*tmp;

  tmp = g_channels;
  write(fd, "Channels matching with \"", 24);
  write(fd, s, strlen(s));
  write(fd, "\": ", 3);
  while (tmp)
    {
      if (strstr(tmp->name, s))
	write(fd, tmp->name, strlen(tmp->name));
      tmp = tmp->next;
    }
  write(fd, "----------", 10);
}
