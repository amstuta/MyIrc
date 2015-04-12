/*
** cmdscli.c for irc in /home/elkaim_r/projects/c/PSU_2014_myirc
** 
** Made by elkaim raphael
** Login   <elkaim_r@epitech.net>
** 
** Started on  Sun Apr 12 21:03:08 2015 elkaim raphael
** Last update Sun Apr 12 21:53:10 2015 elkaim raphael
*/

#include <string.h>
#include <stdio.h>
#include "client.h"

static char	channel[256][4096];
static int	idx = 0;

void	join(char *cmd, int fd)
{
  char	buff[4096];
  char	*chan;

  chan = index(cmd, ' ');
  if (!chan || !chan[1])
    {
      printf("usage: /join channel\n");
      return ;
    }
  chan = chan + 1;
  strcpy(buff, "JOIN #");
  strcpy(channel[idx], chan);
  idx = (idx + 1) % 256;
  strncat(buff, chan, 4096 - strlen(buff));
  send_msg(fd, buff);
}

void	part(char *cmd, int fd)
{
  char	buff[4096];
  char	*chan;
  int	i;

  chan = index(cmd, ' ');
  if (!chan || !chan[1])
    {
      printf("usage: /part channel\n");
      return ;
    }
  i = 0;
  chan = chan + 1;
  while (i < idx)
    {
      if (!strcmp(channel[i], chan))
	strcpy(channel[i], "");
      ++i;
    }
  while ((i - 1) > 0 && !strcmp(channel[i - 1], ""))
    {
      --i;
      --idx;
    }
  strncat(strcpy(buff, "PART #"), chan, 4096 - strlen(buff));
  send_msg(fd, buff);
}

void	msg(char *cmd, int fd)
{
  char	buff[4096];
  char	*dest;
  char	*m;

  strtok(cmd, " ");
  dest = strtok(NULL, " ");
  m = strtok(NULL, " ");
  if (!dest || !m)
    {
      printf("usage: /msg user <message>\n");
      return ;
    }
  strcpy(buff, "PRIVMSG ");
  strncat(buff, dest, 4096 - strlen(buff));
  strncat(buff, " :", 4096 - strlen(buff));
  strncat(buff, m, 4096 - strlen(buff));
  send_msg(fd, buff);
}

void	chanmsg(char *cmd, int fd)
{
  char	buff[4096];

  if (!idx)
    {
      printf("error: you haven't joined a channel yet\n");
      return ;
    }
  strcpy(buff, "PRIVMSG #");
  strncat(buff, channel[idx - 1], 4096 - strlen(buff));
  strncat(buff, " :", 4096 - strlen(buff));
  strncat(buff, cmd, 4096 - strlen(buff));
  send_msg(fd, buff);
}

void	users(char *cmd, int fd)
{
  char	buff[4096];

  (void)cmd;
  strcpy(buff, "NAMES #");
  strncat(buff, channel[idx - (idx > 0)], 4096 - strlen(buff));
  send_msg(fd, buff);
}
