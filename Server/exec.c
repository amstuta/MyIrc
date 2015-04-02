/*
** exec.c for exec in /home/amstuta/rendu/PSU_2014_myirc/Server
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Thu Apr  2 14:47:43 2015 arthur
** Last update Thu Apr  2 16:30:38 2015 arthur
*/

#include <stdlib.h>
#include <string.h>
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
  static char		*tab[10] = {
    "/nick", "/list", "/join",
    "/part", "/users", "/msg",
    "/send_file", "/accept_file", NULL
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

void			exec_cmd(int fd, char *buf)
{
  int			idx;
  static function	tab[8] = {
    &nick, &list, &join, &part, &users,
    &msg, &send_file, &accept_file
  };

  if ((idx = get_idx_cmd(buf)) == -1)
    return ;
  tab[idx](fd, get_args(buf));
}
