/*
** cmdscli2.c for irc in /home/elkaim_r/projects/c/PSU_2014_myirc/Client
** 
** Made by elkaim raphael
** Login   <elkaim_r@epitech.net>
** 
** Started on  Sun Apr 12 21:05:54 2015 elkaim raphael
** Last update Sun Apr 12 21:06:34 2015 elkaim raphael
*/

#include <string.h>
#include <stdio.h>
#include "client.h"

void	list(char *cmd, int fd)
{
  char	buff[4096];
  char	*chan;

  strcpy(buff, "LIST ");
  chan = index(cmd, ' ');
  if (chan && chan[1])
    {
      chan = chan + 1;
      strncat(buff, chan + 1, 4096 - strlen(buff));
    }
  send_msg(fd, buff);
}

void	nick(char *cmd, int fd)
{
  char	buff[4096];
  char	*chan;

  chan = index(cmd, ' ');
  chan = chan + 1;
  if (!chan || !chan[1])
    {
      printf("usage: /nick name");
      return ;
    }
  strcpy(buff, "NICK ");
  strncat(buff, chan, 4096 - strlen(buff));
  send_msg(fd, buff);
}
