/*
** cmd.c for cmd in /home/amstuta/rendu/PSU_2014_myirc/Client
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Thu Apr  2 11:31:26 2015 arthur
** Last update Thu Apr  2 11:45:32 2015 arthur
*/

#include <string.h>
#include "client.h"

int		check_cmd(char *cmd)
{
  int		i;
  static char	*tab[10] = {"/nick", "/list",
			   "/join", "/part",
			   "/users", "/msg",
			   "/msg", "/send_file",
			   "/accept_file", NULL};

  i = 0;
  while (tab[i])
    {
      if (!strncmp(cmd, tab[i], strlen(tab[i])))
	return (1);
      ++i;
    }
  return (0);
}
