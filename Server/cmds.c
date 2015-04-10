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

void		nick(t_client *cli, t_packet *pack)
{
  if (!pack->arg[0])
    {
      send_msg(cli->fd, "461 NICK :Needs more params");
      return ;
    }
  if (check_nick(pack->arg[0], cli->fd) == 1)
    return ;
  strcpy(cli->login, pack->arg[0]);
}

void		userlog(t_client *cli, t_packet *pack)
{
  if (!pack->arg[0] || !pack->arg[1] || !pack->arg[2] || !pack->trailer)
    {
      send_msg(cli->fd, "461 USER :Needs more params");
      return ;
    }
  if (strcmp(cli->rname, "") && strcmp(cli->login, ""))
    {
      send_msg(cli->fd, "462 :You cannot Reregister");
      return ;
    }
  strcpy(cli->rname, pack->trailer);
}

void		passer(t_client *cli, t_packet *pack)
{
  if (!pack->arg[0])
    {
      send_msg(cli->fd, "461 PASS :Needs more params");
      return ;
    }
  if (strcmp(cli->rname, "") && strcmp(cli->login, ""))
    {
      send_msg(cli->fd, "462 :You cannot Reregister");
      return ;
    }
}

void		list(t_client *cli, t_packet *pack)
{
  //RFC GUD
  // NORME NOT GUD
  if (!pack->arg[0])
    list_channels(cli->fd);
  else
    search_channels(cli->fd, pack->arg[0]);
}

void		join(t_client *cli, t_packet *pack)
{
  char		buff[LINE_SIZE];

  memset(buff, 0, LINE_SIZE);
  if (!pack->arg[0])
    {
      send_msg(cli->fd, "461 JOIN :Needs more params");
      return ;
    }
  strcpy(cli->channel, pack->arg[0]);
  if (!channel_exists(pack->arg[0]))
    add_channel(pack->arg[0]);
  broadcast(strcat(strcat(strcat(strcat(buff, ":"), cli->login), " JOIN :"), pack->arg[0]), pack->arg[0]);
  users(cli, pack);
}

void		part(t_client *cli, t_packet *pack)
{
  char		buff[LINE_SIZE];

  memset(buff, 0, LINE_SIZE);
  if (strcmp(cli->channel, pack->arg[0]))
    {
      send_msg(cli->fd, "442 :You're not on that channel");
      return ;
    }
  broadcast(strcat(strcat(strcat(strcat(buff, ":"), cli->login), " PART :"), pack->arg[0]), pack->arg[0]);
  strcpy(cli->channel, "");
}

void		users(t_client *cli, t_packet *pack) 
{
  t_client	*tmp;
  char		buff[LINE_SIZE];

  tmp = g_clients;
  (void)pack;
  memset(buff, 0, LINE_SIZE);
  strcat(strcat(strcat(buff, "353 "), cli->channel), " :");
  while (tmp)
    {
      if (tmp->channel)
	if (!strcmp(tmp->channel, cli->channel))
	  {
	    strcat(buff, tmp->login);
	    strcat(buff, " ");
	  }
      tmp = tmp->next;
    }
  send_msg(cli->fd, buff);
  send_msg(cli->fd, strcat(strcat(strcpy(buff, "366 "), cli->channel), " :End of name list"));
}

void		msg(t_client *cli, t_packet *pack)
{
  char		buf[LINE_SIZE];

  memset(buf, 0, LINE_SIZE);
  if (!pack->trailer)
    send_msg(cli->fd, "412 :No text to send");
  if (!pack->arg[0])
    send_msg(cli->fd, "411 :No recipient given");
  if (!pack->trailer || !pack->arg[0])
    return ;
  strcat(buf, ":");
  strcat(buf, cli->login);
  strcat(buf, " ");
  strcat(buf, "PRIVMSG :");
  strcat(buf, pack->trailer);
  broadcast(buf, pack->arg[0]);
}

void		send_file(t_client *cli, t_packet *pack)
{
  (void)cli;
  (void)pack;
}

void		accept_file(t_client *cli, t_packet *pack)
{
  (void)cli;
  (void)pack;
}
