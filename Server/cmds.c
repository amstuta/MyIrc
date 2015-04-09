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

  //RFC -> GUD
  //NORME -> NOT GUD
  if (!pack->arg[0])
    {
      send_msg(fd, "461 NICK :Needs more params");
      return ;
    }
  if (check_nick(pack->arg[0], fd) == 1)
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
  //RFC GUD
  // NORME NOT GUD
  if (!pack->arg[0])
    list_channels(fd);
  else
    search_channels(fd, pack->arg[0]);
}

void		join(int fd, t_packet *pack)
{
  t_client	*tmp;
  char		buff[LINE_SIZE];

  tmp = g_clients;
  memset(buff, 0, LINE_SIZE);
  if (!pack->arg[0] || strlen(pack->arg[0]) > 20)
    {
      send_msg(fd, "461 NICK :Needs more params");
      return ;
    }
  while (tmp)
    {
      if (tmp->fd == fd)
	{
	  strcpy(tmp->channel, pack->arg[0]);
	  break ;
	}
      tmp = tmp->next;
    }
  if (!channel_exists(pack->arg[0]))
    add_channel(pack->arg[0]);
  broadcast(strcat(strcat(strcat(strcat(buff, ":"), tmp->login), " JOIN :"), pack->arg[0]), pack->arg[0]);
}

void		part(int fd, t_packet *pack)
{
  t_client	*tmp;
  char		buff[LINE_SIZE];

  tmp = g_clients->next;
  memset(buff, 0, LINE_SIZE);
  while (tmp)
    {
      if (tmp->fd == fd)
	{
	  if (strcmp(tmp->channel, pack->arg[0]))
	    {
	      send_msg(fd, "442 :You're not on that channel");
	      return ;
	    }
	  break ;
	}
      tmp = tmp->next;
    }
  broadcast(strcat(strcat(strcat(strcat(buff, ":"), tmp->login), " PART :"), pack->arg[0]), pack->arg[0]);
  strcpy(tmp->channel, "");
}

void		users(int fd, t_packet *pack) 
{
  t_client	*tmp;
  char		*chan;
  char		buff[LINE_SIZE];

  tmp = g_clients;
  if (!(chan = get_client_channel(fd)))
    return ;
  (void)pack;
  /*  if (!channel_exists(args))
    {
      write(fd, "Error: channel doesn't exist", 28);
      return ;
      }*/
  //write(fd, "Channel users:", 14);
  strcat(strcat(strcat(buff, "353 "), chan), " :");
  while (tmp)
    {
      if (tmp->channel)
	if (!strcmp(tmp->channel, chan))
	  {
	    strcat(buff, tmp->login);
	    strcat(buff, " ");
	  }
      tmp = tmp->next;
    }
  send_msg(fd, buff);
  send_msg(fd, strcat(strcat(strcpy(buff, "366 "), chan), " :End of name list"));
}

void		msg(int fd, t_packet *pack)
{
  //  int		cfd;
  //char		*msg;
  //char		*user;
  char		*sender;
  char		buf[LINE_SIZE];

  memset(buf, 0, LINE_SIZE);
  if (!pack->trailer)
    send_msg(fd, "412 :No text to send");
  if (!pack->arg[0])
    send_msg(fd, "411 :No recipient given");
  if (!pack->trailer || !pack->arg[0])
    return ;
  if ((sender = get_login_from_fd(fd)))
    {
      strcat(buf, ":");
      strcat(buf, sender);
      strcat(buf, " ");
    }
  strcat(buf, "PRIVMSG :");
  strcat(buf, pack->trailer);
  broadcast(buf, pack->arg[0]);
  /*  if (!(user = strtok(pack->arg[0], " ")) ||
      !(msg = strtok(NULL, "\0")))
    return ;
  if (!pack->arg[0] || !(cfd = get_user_fd(user)))
    return ;
  strcat(buf, ": ");
  strcat(buf, msg);
  write(cfd, buf, strlen(buf));*/
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
