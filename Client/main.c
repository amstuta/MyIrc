/*
** main.c for client in /home/amstuta/rendu/PSU_2014_myirc/Client
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Fri Mar 27 13:07:57 2015 arthur
** Last update Mon Apr  6 15:47:12 2015 arthur
*/

#include <stdlib.h>
#include <stdio.h>
#include "client.h"

int			main()
{
  struct termios	term;

  if (set_canon_off(&term) == -1)
    {
      printf("Couldn't set raw mode, exiting...\n");
      return (EXIT_FAILURE);
    }
  read_cmd();
  reset_canon(&term);
  return (EXIT_SUCCESS);
}
