/*
** cmds.c for cmds in /home/amstuta/rendu/PSU_2014_myirc/Server
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Thu Apr  2 15:17:38 2015 arthur
** Last update Tue Apr  7 13:42:41 2015 arthur
*/

#include <stdio.h>
#include <unistd.h>
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
  if (!args)
    list_channels(fd);
  else
    search_channels(fd, args);
}

void		join(int fd, char *args)
{
  t_client	*tmp;

  tmp = g_clients;
  if (!args || strlen(args) > 20)
    {
      write(fd, "Error: invalid channel name", 27);
      return ;
    }
  while (tmp)
    {
      if (tmp->fd == fd)
	tmp->channel = strdup(args);
      tmp = tmp->next;
    }
  if (!channel_exists(args))
    add_channel(args);
}

void		part(int fd, char *args)
{
  t_client	*tmp;

  tmp = g_clients;
  while (tmp)
    {
      if (tmp->fd == fd)
	{
	  if (strcmp(tmp->channel, args))
	    {
	      write(fd, "Error: you didn't join that channel", 35);
	      return ;
	    }
	  tmp->channel = NULL;
	}
      tmp = tmp->next;
    }
}

void		users(int fd, char *args)
{
  t_client	*tmp;
  char		*chan;

  tmp = g_clients;
  (void)args;
  if (!(chan = get_client_channel(fd)))
    return ;
  /*  if (!channel_exists(args))
    {
      write(fd, "Error: channel doesn't exist", 28);
      return ;
      }*/
  write(fd, "Channel users:", 14);
  while (tmp)
    {
      if (tmp->channel)
	if (!strcmp(tmp->channel, chan))
	  write(fd, tmp->login, strlen(tmp->login));
      tmp = tmp->next;
    }
  write(fd, "----------", 10);
}

void		msg(int fd, char *args)
{
  int		cfd;
  char		*msg;
  char		*user;
  char		*sender;
  char		buf[LINE_SIZE];

  memset(buf, 0, LINE_SIZE);
  if (!(user = strtok(args, " ")) ||
      !(msg = strtok(NULL, "\0")))
    return ;
  if (!args || !(cfd = get_user_fd(user)))
    return ;
  if ((sender = get_login_from_fd(fd)))
    strcpy(buf, sender);
  strcat(buf, ": ");
  strcat(buf, msg);
  write(cfd, buf, strlen(buf));
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
