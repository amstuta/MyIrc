/*
** cmds2.c for irc in /home/elkaim_r/projects/c/PSU_2014_myirc
** 
** Made by elkaim raphael
** Login   <elkaim_r@epitech.net>
** 
** Started on  Sun Apr 12 21:00:23 2015 elkaim raphael
** Last update Sun Apr 12 21:00:26 2015 elkaim raphael
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "server.h"

void		part(t_client *cli, t_packet *pack)
{
  char		buff[LINE_SIZE];

  memset(buff, 0, LINE_SIZE);
if (!pack->arg[0])
    {
      send_msg(cli->fd, "461 JOIN :Needs more params");
      return ;
    }
  if (!has_channel(&cli->channel, pack->arg[0]))
    {
      send_msg(cli->fd, "442 :You're not on that channel");
      return ;
    }
  if (pack->arg[0][0] != '#' && pack->arg[0][0] != '&')
    {
      send_msg(cli->fd, CO(CO(CP(buff, "403 "), pack->arg[0]), NOCHAN));
      return ;
    }
  broadcast(CO(CO(CO(CO(buff, ":"), cli->login),
		  " PART :"), pack->arg[0]), pack->arg[0]);
  del_channel(&cli->channel, pack->arg[0]);
}

void		users(t_client *cli, t_packet *pack)
{
  t_client	*tmp;
  char		buff[LINE_SIZE];

  tmp = g_clients;
  (void)pack;
  memset(buff, 0, LINE_SIZE);
  if (!pack->arg[0])
    {
      send_msg(cli->fd, "461 NAMES :Needs more params");
      return ;
    }
  strcat(strcat(strcat(buff, "353 "), pack->arg[0]), " :");
  while (tmp)
    {
      if (tmp->channel)
	if (has_channel(&tmp->channel, pack->arg[0]))
	  {
	    strcat(buff, tmp->login);
	    strcat(buff, " ");
	  }
      tmp = tmp->next;
    }
  send_msg(cli->fd, buff);
  send_msg(cli->fd, CO(CO(CP(buff, "366 "), pack->arg[0]),
		       " :End of name list"));
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

void		quit(t_client *cli, t_packet *pack)
{
  char		buff[LINE_SIZE];
  t_channel	*tmp;
  int		fds;

  tmp = cli->channel;
  fds = cli->fd;
  (void)pack;
  memset(buff, 0, LINE_SIZE);
  while (tmp)
    {
      broadcast(CO(CO(CO(buff, ":"), cli->login), " QUIT")
		, tmp->name);
      tmp = tmp->next;
    }
  remove_client(fds);
  close(fds);
}
