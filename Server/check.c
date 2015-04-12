/*
** check.c for irc in /home/elkaim_r/projects/c/PSU_2014_myirc
** 
** Made by elkaim raphael
** Login   <elkaim_r@epitech.net>
** 
** Started on  Sun Apr 12 21:01:07 2015 elkaim raphael
** Last update Sun Apr 12 21:01:08 2015 elkaim raphael
*/

#include <ctype.h>
#include <string.h>
#include "server.h"

int		alphanum(char *str)
{
  int		i;

  i = 0;
  while (str[i])
    {
      if (!isalnum(str[i]) && str[i] != '_')
	return (0);
      ++i;
    }
  return (1);
}

int		check_nick(char *nick, int fd)
{
  t_client	*tmp;
  char		buff[LINE_SIZE];

  tmp = g_clients->next;
  memset(buff, 0, LINE_SIZE);
  if (strlen(nick) > 9 || !alphanum(nick))
    {
      send_msg(fd, strcat(strcat(strcat(buff, "432 "), nick),
			  " :Erroneus Nickname"));
      return (1);
    }
  while (tmp)
    {
      if (!strcmp(tmp->login, nick))
	{
	  send_msg(fd, strcat(strcat(buff, "433 "), nick));
	  return (1);
	}
      tmp = tmp->next;
    }
  return (0);
}
