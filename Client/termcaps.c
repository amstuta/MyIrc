/*
** termcaps.c for termcaps in /home/amstuta/rendu/PSU_2014_myirc/Client
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Mon Apr  6 15:35:52 2015 arthur
** Last update Mon Apr  6 15:45:47 2015 arthur
*/

#include <curses.h>
#include "client.h"

int	set_canon_off(struct termios *a)
{
  if (tcgetattr(0, a) == -1)
    return (-1);
  a->c_lflag &= ~ICANON;
  a->c_lflag &= ~ECHO;
  a->c_cc[VMIN] = 1;
  a->c_cc[VTIME] = 0;
  if (tcsetattr(0, TCSANOW, a) == -1)
    return (-1);
  return (0);
}

void	reset_canon(struct termios *a)
{
  a->c_lflag ^= ~ICANON;
  a->c_lflag ^= ~ECHO;
  a->c_cc[VMIN] = 1;
  if (tcsetattr(0, TCSANOW, a) == -1)
    return ;
}
