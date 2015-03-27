/*
** client.c for client in /home/amstuta/rendu/PSU_2014_myirc/Server
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Fri Mar 27 15:32:10 2015 arthur
** Last update Fri Mar 27 16:01:58 2015 arthur
*/

#include <string.h>
#include <stdlib.h>
#include "server.h"

void		add_client(t_client **clients, int fd, char *login)
{
  t_client	*new;
  t_client	*tmp;

  if (!(new = malloc(sizeof(t_client))))
    return ;
  new->fd = fd;
  new->login = strdup(login);
  new->next = NULL;
  if (*clients == NULL)
    *clients = new;
  else
    {
      tmp = *clients;
      while (tmp->next)
	tmp = tmp->next;
      tmp->next = new;
    }
}

void		remove_client(t_client **clients, int fd)
{
  t_client	*tmp;
  t_client	*save;

  save = NULL;
  tmp = *clients;
  while (tmp && tmp->fd != fd)
    {
      save = tmp;
      tmp = tmp->next;
    }
  if (tmp == NULL)
    return ;
  if (save == NULL)
    *clients = tmp->next;
  else
    save->next = tmp->next;
  free(tmp->login);
  free(tmp);
}
