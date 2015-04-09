/*
** exec.c for exec in /home/amstuta/rendu/PSU_2014_myirc/Server
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Thu Apr  2 14:47:43 2015 arthur
** Last update Wed Apr  8 17:58:08 2015 elkaim raphael
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "server.h"

char			*get_args(char *cmd)
{
  char			*c;
  char			tmp[LINE_SIZE];

  strcpy(tmp, cmd);
  if ((c = strtok(tmp, " ")) == NULL)
    return (NULL);
  if (strlen(cmd) > strlen(c))
    return (&cmd[strlen(c) + 1]);
  return (NULL);
}

int			get_idx_cmd(char *cmd)
{
  int			i;
  static const char    	*tab[10] = {
    "NICK", "LIST", "JOIN",
    "PART", "NAMES", "PRIVMSG",
    "SF", "AF", NULL
  };

  i = 0;
  while (tab[i])
    {
      if (!strncmp(cmd, tab[i], strlen(tab[i])))
	return (i);
      ++i;
    }
  return (-1);
}

void			send_msg_all(int fd, char *msg)
{
  t_client		*tmp;
  char			*channel;

  tmp = g_clients;
  if (!(channel = get_client_channel(fd)))
    return ;
  while (tmp)
    {
      if (!strcmp(channel, tmp->channel))
	write(tmp->fd, msg, strlen(msg));
      tmp = tmp->next;
    }
}

void			exec_cmd(t_client *cli)
{
  int			idx;
  t_cmd			*tmp;
  t_packet		res;
  static function	tab[8] = {
    &nick, &list, &join, &part, &users,
    &msg, &send_file, &accept_file
  };

  tmp = cli->cmd_in;
  while (tmp)
    {
      fill_packet(tmp->com, &res);
      printf("voici la commande: %s  \n", res.command);
      if ((idx = get_idx_cmd(res.command)) == -1)
	printf("invalid command\n");
      else
	tab[idx](cli->fd, &res);
      tmp = tmp->next;
    }
  cli->cmd_in = NULL;
}
