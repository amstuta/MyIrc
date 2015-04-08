/*
** circ_buff.c for irc in /home/elkaim_r/projects/c/PSU_2014_myirc/Server
** 
** Made by elkaim raphael
** Login   <elkaim_r@epitech.net>
** 
** Started on  Tue Apr  7 12:55:31 2015 elkaim raphael
** Last update Wed Apr  8 12:48:22 2015 elkaim raphael
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "server.h"

void	add_command(t_cmd **com, char *pack, e_bool flag)
{
  t_cmd	*new;
  t_cmd	*tmp;

  if ((new = malloc(sizeof(t_cmd))) == NULL)
    exit(EXIT_FAILURE);
  strcpy(new->com, pack);
  new->in_out = flag;
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
  t_cmd	*tmp;

  if (*root == NULL)
    return ;
  tmp = *root;
  if (*root == del)
    {
      *root = (*root)->next;
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
      add_command(root, res, true);
      if (value)
	value = NULL;
    }
}

void	write_reps(int fd, t_cmd **cmds)
{
  t_cmd	*tmp;
  t_cmd	*save;

  tmp = *cmds;
  save = NULL;
  while (tmp)
    {
      if (save != NULL)
	{
	  remove_command(cmds, save);
	  save = NULL;
	}
      if(tmp->in_out == false)
	{
	  write(fd, tmp->com, strlen(tmp->com));
	  save = tmp;
	}
      tmp = tmp->next;
    }
}
