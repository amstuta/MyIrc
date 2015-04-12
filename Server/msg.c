/*
** msg.c for irc in /home/elkaim_r/projects/c/PSU_2014_myirc
** 
** Made by elkaim raphael
** Login   <elkaim_r@epitech.net>
** 
** Started on  Sun Apr 12 20:59:40 2015 elkaim raphael
** Last update Sun Apr 12 20:59:41 2015 elkaim raphael
*/

#include <string.h>
#include <unistd.h>
#include "server.h"

void	send_msg(int fd, char *msg)
{
  char	buff[LINE_SIZE];

  strcpy(buff, msg);
  strcat(buff, END);
  write(fd, buff, strlen(buff));
}
