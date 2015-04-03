/*
** io.c for io in /home/amstuta/rendu/PSU_2014_myirc/Server
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Fri Apr  3 12:19:34 2015 arthur
** Last update Fri Apr  3 12:26:19 2015 arthur
*/

#include "server.h"

void		check_clients_fd_in(fd_set *readfds)
{
  t_client	*tmp;

  tmp = g_clients;
  while (tmp)
    {
      if (FD_ISSET(tmp->fd, readfds) != 0)
	read_client(tmp->fd);
      tmp = tmp->next;
    }
}

void		check_clients_fd_out(fd_set *writefds)
{
  (void)writefds;
}
