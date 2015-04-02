/*
** cmds.c for cmds in /home/amstuta/rendu/PSU_2014_myirc/Server
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Thu Apr  2 15:17:38 2015 arthur
** Last update Thu Apr  2 16:32:58 2015 arthur
*/

#include <stdio.h>
#include <string.h>
#include "server.h"

void		nick(int fd, char *args)
{
  t_client	*tmp;

  //Checker nom
  if (!args)
    return ;
  tmp = g_clients;
  while (tmp)
    {
      if (tmp->fd == fd)
	{
	  tmp->login = strdup(args);
	  return ;
	}
      tmp = tmp->next;
    }
}

void		list(int fd, char *args)
{
  (void)fd;
  (void)args;
}

void		join(int fd, char *args)
{
  (void)fd;
  (void)args;
}

void		part(int fd, char *args)
{
  (void)fd;
  (void)args;
}

void		users(int fd, char *args)
{
  (void)fd;
  (void)args;
}

void		msg(int fd, char *args)
{
  (void)fd;
  (void)args;
}

void		send_file(int fd, char *args)
{
  (void)fd;
  (void)args;
}

void		accept_file(int fd, char *args)
{
  (void)fd;
  (void)args;
}
