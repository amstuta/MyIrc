/*
** circ_buff.c for irc in /home/elkaim_r/projects/c/PSU_2014_myirc/Server
** 
** Made by elkaim raphael
** Login   <elkaim_r@epitech.net>
** 
** Started on  Tue Apr  7 12:55:31 2015 elkaim raphael
** Last update Tue Apr  7 13:35:52 2015 elkaim raphael
*/

#include <stdlib.h>
#include "server.h"

void	add_command(t_cmd **com, char *pack)
{
  t_com	*new;
  t_com	*tmp;

  if ((new = malloc(sizeof(t_cmd))) == NULL)
    exit(EXIT_FAILURE);
  strcpy(new->com, pack);
  new->next = NULL;
  if (*com == NULL)
    *com = new;
  else
    {
      tmp = *com;
      while (tmp->next)
	tmp = tmp->next;
      tmp->next = new;
    }
}

void	remove_command(t_cmd **root, t_cmd *del)
{
  t_com	*tmp;

  if (*root == NULL)
    return ;
  tmp = *root;
  if (*root == del)
    {
      *root = *root->next;
      free(del);
      return ;
    }
  while (tmp->next && tmp->next != del)
    tmp = tmp->next;
  tmp->next = tmp->next->next;
  free(del);
}

void	command_to_list(char *buffer, t_cmd **root)
{
  char	*value;
  char	*res;

  value = buffer;
  while ((res = strtok(value, "\r\n")) != NULL)
    {
      add_command(root, res);
      if (value)
	value = NULL;
    }
}
