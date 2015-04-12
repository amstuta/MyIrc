/*
** msg.c for irc in /home/elkaim_r/projects/c/PSU_2014_myirc
** 
** Made by elkaim raphael
** Login   <elkaim_r@epitech.net>
** 
** Started on  Sun Apr 12 20:59:23 2015 elkaim raphael
** Last update Sun Apr 12 20:59:24 2015 elkaim raphael
*/

#include <string.h>
#include <unistd.h>
#include "client.h"

void	send_msg(int fd, char *cmd)
{
  char	buff[4096];

  strcpy(buff, cmd);
  strcat(buff, "\r\n");
  write(fd, buff, strlen(buff));
}
