/*
** exec.c for irc in /home/elkaim_r/projects/c/PSU_2014_myirc
** 
** Made by elkaim raphael
** Login   <elkaim_r@epitech.net>
** 
** Started on  Sun Apr 12 21:01:38 2015 elkaim raphael
** Last update Sun Apr 12 21:45:54 2015 elkaim raphael
*/

#include <unistd.h>
#include <string.h>
#include "client.h"

int			get_idx_cmd(char *cmd)
{
  int			i;
  static const char	*tab[7] = {
    "/join", "/part", "/msg",
    "/users", "/nick", "/list", NULL
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

void			exec_cmd(char *cmd, int fd)
{
  int			idx;
  static function	tab[6] = {
    &join, &part, &msg, &users, &nick,
    &list
  };

  if ((idx = get_idx_cmd(cmd)) == -1)
    chanmsg(cmd, fd);
  else
    tab[idx](cmd, fd);
}

int			get_idx_cmd_srv(char *cmd)
{
  int			i;
  static const char	*tab[7] = {
    "PRIVMSG", "JOIN", "PART",
    "QUIT", NULL
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

void			exec_cmd_srv(char *cmd)
{
  int			idx;
  t_packet		res;
  char			cp[4096];
  static function2	tab[6] = {
    &smsg, &sjoin, &spart, &squit
  };

  strcpy(cp, cmd);
  fill_packet(cmd, &res);
  if ((idx = get_idx_cmd_srv(res.command)) == -1)
    {
      write(1, "\r\x1b[34m", 7);
      write(1, cp, strlen(cp));
      write(1, "\x1b[0m", 6);
    }
  else
    tab[idx](&res, 0);
}
