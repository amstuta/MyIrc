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
  char		buff[4096];

  memset(buff, 0, 4096);
  if (!pack->arg[0])
    {
      send_msg(cli->fd, "461 NICK :Needs more params");
      return ;
    }
  if (check_nick(pack->arg[0], cli->fd) == 1)
    return ;
  strcpy(cli->login, pack->arg[0]);
  if (strcmp(cli->rname, "") && strcmp(cli->login, "") && !cli->registered)
    {
      send_msg(cli->fd, CO(CO(buff, "NICK "), cli->login));
      send_msg(cli->fd, CO(CP(buff, "USER "), cli->login));
      cli->registered = 1;
    }
}

void		userlog(t_client *cli, t_packet *pack)
{
  char		buff[4096];

  memset(buff, 0, 4096);
  if (!pack->arg[0] || !pack->arg[1] || !pack->arg[2] || !pack->trailer
      || !strcmp(pack->trailer, ""))
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
  if (strcmp(cli->rname, "") && strcmp(cli->login, ""))
    {
      send_msg(cli->fd, CO(CO(buff, "NICK "), cli->login));
      send_msg(cli->fd, CO(CP(buff, "USER "), cli->login));
      cli->registered = 1;
    }
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
  if (pack->arg[0][0] != '#' && pack->arg[0][0] != '&')
    {
      send_msg(cli->fd, CO(CO(CP(buff, "403 "), pack->arg[0]), NOCHAN));
      return ;
    }
  add_cchannel(&cli->channel, pack->arg[0]);
  if (!channel_exists(pack->arg[0]))
    add_channel(pack->arg[0]);
  broadcast(CO(CO(CO(CO(buff, ":"), cli->login),
		  JOIN), pack->arg[0]), pack->arg[0]);
  CP(buff, "332 ");
  CO(buff, pack->arg[0]);
  CO(buff, " : ");
  send_msg(cli->fd, buff);
  users(cli, pack);
}
