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
  strcpy(new->name, name);
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

void		list_channels(int fd)
{
  t_channel	*tmp;
  char		buff[LINE_SIZE];

  tmp = g_channels;
  memset(buff, 0, LINE_SIZE);
  send_msg(fd, "321 Channels :list channels");
  while (tmp)
    {
      send_msg(fd, strcat(strcat(strcat(buff, "322 "),
				 tmp->name), " 1 :"));
      strcpy(buff, "");
      tmp = tmp->next;
    }
  send_msg(fd, "323 :End of list");
}

void		search_channels(int fd, char *s)
{
  t_channel	*tmp;
  char		buff[LINE_SIZE];

  tmp = g_channels;
  memset(buff, 0, LINE_SIZE);
  send_msg(fd, "321 Channels :list channels");
  while (tmp)
    {
      if (strstr(tmp->name, s))
	send_msg(fd, strcat(strcat(strcat(buff, "322 "),
				   tmp->name), " 1 :"));
      strcpy(buff, "");
      tmp = tmp->next;
    }
  send_msg(fd, "323 :End of list");
}

void		broadcast(char *message, char *channel)
{
  t_client	*tmp;

  tmp = g_clients->next;
  if (channel[0] != '#' && channel [0] != '&')
    {
      while (tmp)
	{
	  if (!strcmp(tmp->login, channel))
	    {
	      send_msg(tmp->fd, message);
	      return ;
	    }
	  tmp = tmp->next;
	}
      return ;
    }
  while (tmp)
    {
      if (has_channel(&tmp->channel, channel))
	send_msg(tmp->fd, message);
      tmp = tmp->next;
    }
}
