/*
** client.c for client in /home/amstuta/rendu/PSU_2014_myirc/Server
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Fri Mar 27 15:32:10 2015 arthur
** Last update Fri Mar 27 16:43:15 2015 arthur
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "server.h"

void		add_channel(t_channel **channels, char *name)
{
  t_channel	*new;
  t_channel	*tmp;

  if (!(new = malloc(sizeof(t_channel))) || !name)
    return ;
  new->name = strdup(name);
  new->next = NULL;
  if (*channels == NULL)
    *channels = new;
  else
    {
      tmp = *channels;
      while (tmp->next)
	tmp = tmp->next;
      tmp->next = new;
    }
}

void		list_channels(t_channel *channels, int fd)
{
  int		idx;
  t_channel	*tmp;
  char		buf[4096];

  idx = 0;
  tmp = channels;
  while (tmp)
    {
      if ((idx + strlen(tmp->name)) < 4096)
	{
	  strcat(buf, tmp->name);
	  strcat(buf, " ");
	  idx += strlen(tmp->name) + 1;
	}
      tmp = tmp->next;
    }
  buf[idx] = 0;
  write(fd, buf, strlen(buf));
}

void		search_channels(t_channel *channels, char *s, int fd)
{
  int		idx;
  t_channel	*tmp;
  char		buf[4096];

  idx = 0;
  tmp = channels;
  while (tmp)
    {
      if ((idx + strlen(tmp->name)) < 4096)
	{
	  if (strstr(tmp->name, s))
	    {
	      strcat(buf, tmp->name);
	      strcat(buf, " ");
	      idx += strlen(tmp->name) + 1;
	    }
	}
      tmp = tmp->next;
    }
  buf[idx] = 0;
  write(fd, buf, strlen(buf));
}
