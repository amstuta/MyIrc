/*
** read.c for read in /home/amstuta/rendu/PSU_2014_myirc/Client
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Fri Mar 27 16:03:33 2015 arthur
** Last update Fri Mar 27 16:30:07 2015 arthur
*/

#include <string.h>
#include <unistd.h>
#include "client.h"

int	check_cmd(char *cmd)
{  
  if (!strncmp(cmd, SERVER, strlen(SERVER)))
    {
      connect_to_serv(cmd);
      return (1);
    }
  return (0);
}

void	read_cmd()
{
  int	rd;
  char	buff[LINE_SIZE];
  
  while (1)
    {
      if ((rd = read(0, buff, LINE_SIZE - 1)) <= 0)
	return ;
      buff[rd] = 0;
      if (!check_cmd(buff))
	write(1, "Error: unknown command\n", 23);
    }
}
