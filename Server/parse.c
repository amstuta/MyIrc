/*
** parse.c for irc in /home/elkaim_r/projects/c/PSU_2014_myirc/Server
** 
** Made by elkaim raphael
** Login   <elkaim_r@epitech.net>
** 
** Started on  Wed Apr  8 14:00:34 2015 elkaim raphael
** Last update Wed Apr  8 15:13:48 2015 elkaim raphael
*/

#include <string.h>
#include "server.h"

int	get_prefixe(char *cmd, t_packet *pack)
{
  if (cmd[0] == ':')
    {
      pack->prefix = strndup(cmd + 1, strcspn(cmd, " "));
      return (0);
    }
  pack->prefix = NULL;
  return (1);
}

int	get_command(char *cmd, t_packet *pack, int *idx)
{
  if (!cmd)
    return (1);
  pack->command = strndup(cmd, strcspn(cmd, " "));
  if (idx)
    *idx = strcspn(cmd, " ");
  if (pack->command)
    return (0);
  return (1);
}

int	get_params(char *cmd, t_packet *packet)
{
  int	i;
  char	*arg;
  char	*cmda;

  i = 0;
  cmda = cmd;
  while ((arg = strtok(cmda, " ")))
    {
      packet->arg[i] = arg;
      if (cmda)
	cmda = NULL;
      ++i;
    }
  packet->arg[i] = NULL;
  packet->argn = i;
  return (0);
}

int	get_trailer(char *cmd, t_packet *packet)
{
  if (index(cmd, ':') == NULL)
    {
      packet->trailer = NULL;
      return (1);
    }
  packet->trailer = strdup(index(cmd, ':') + 1);
  index(cmd, ':')[0] = 0;
  if (packet->trailer)
    return (0);
  return (1);
}

int	fill_packet(char *cmd, t_packet *pack)
{
  int	idx;

  idx = 0;
  if (get_prefixe(cmd, pack) == 0)
    {
      cmd = index(cmd, ' ') + 1;
    }
  get_command(cmd, pack, &idx);
  get_trailer(&cmd[idx], pack);
  get_params(&cmd[idx], pack);
  return (0);
}
