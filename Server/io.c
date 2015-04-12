/*
** io.c for io in /home/amstuta/rendu/PSU_2014_myirc/Server
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Fri Apr  3 12:19:34 2015 arthur
** Last update Wed Apr  8 16:44:27 2015 elkaim raphael
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "server.h"

void		check_clients_fd_in(fd_set *readfds, t_client *save)
{
  t_client	*tmp;

  tmp = g_clients->next;
  while (tmp)
    {
      if (save)
	{
	  remove_client(save->fd);
	  save = NULL;
	}
      if (FD_ISSET(tmp->fd, readfds) != 0)
	{
	  if (read_client(tmp) == 1)
	    save = tmp;
	}
      tmp = tmp->next;
    }
  if (save)
    {
      remove_client(save->fd);
      save = NULL;
    }
}

void		check_clients_fd_out(fd_set *writefds)
{
  t_client	*tmp;
  t_client	*save;

  tmp = g_clients->next;
  save = NULL;
  (void)writefds;
  while (tmp)
    tmp = tmp->next;
  if (save)
    {
      remove_client(save->fd);
      save = NULL;
    }
}
