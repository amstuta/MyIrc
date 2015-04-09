/*
** cmds.c for cmds in /home/amstuta/rendu/PSU_2014_myirc/Server
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Thu Apr  2 15:17:38 2015 arthur
** Last update Wed Apr  8 18:46:50 2015 elkaim raphael
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "server.h"

void		nick(int fd, t_packet *pack)
{
  t_client	*tmp;

  if (!pack->arg[0])
    return ;
  tmp = g_clients;
  while (tmp)
    {
      if (tmp->fd == fd)
	{
	  strcpy(tmp->login, pack->arg[0]);
	  return ;
	}
      tmp = tmp->next;
    }
}

void		list(int fd, t_packet *pack)
{
  if (!pack->arg[0])
    list_channels(fd);
  else
    search_channels(fd, pack->arg[0]);
}

void		join(int fd, t_packet *pack)
{
  t_client	*tmp;

  tmp = g_clients;
  if (!pack->arg[0] || strlen(pack->arg[0]) > 20)
    {
      write(fd, "Error: invalid channel name", 27);
      return ;
    }
  while (tmp)
    {
      if (tmp->fd == fd)
	strcpy(tmp->channel, pack->arg[0]);
      tmp = tmp->next;
    }
  if (!channel_exists(pack->arg[0]))
    add_channel(pack->arg[0]);
}

void		part(int fd, t_packet *pack)
{
  t_client	*tmp;

  tmp = g_clients;
  while (tmp)
    {
      if (tmp->fd == fd)
	{
	  if (strcmp(tmp->channel, pack->arg[0]))
	    {
	      write(fd, "Error: you didn't join that channel", 35);
	      return ;
	    }
	  strcpy(tmp->channel, "");
	}
      tmp = tmp->next;
    }
}

void		users(int fd, t_packet *pack) 
{
  t_client	*tmp;
  char		*chan;

  tmp = g_clients;
  if (!(chan = get_client_channel(fd)))
    return ;
  (void)pack;
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

void		msg(int fd, t_packet *pack)
{
  int		cfd;
  char		*msg;
  char		*user;
  char		*sender;
  char		buf[LINE_SIZE];

  memset(buf, 0, LINE_SIZE);
  if (!(user = strtok(pack->arg[0], " ")) ||
      !(msg = strtok(NULL, "\0")))
    return ;
  if (!pack->arg[0] || !(cfd = get_user_fd(user)))
    return ;
  if ((sender = get_login_from_fd(fd)))
    strcpy(buf, sender);
  strcat(buf, ": ");
  strcat(buf, msg);
  write(cfd, buf, strlen(buf));
}

void		send_file(int fd, t_packet *pack)
{
  (void)fd;
  (void)pack;
}

void		accept_file(int fd, t_packet *pack)
{
  (void)fd;
  (void)pack;
}
