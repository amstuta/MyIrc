#include <stdlib.h>
#include <string.h>
#include "server.h"

void		add_cchannel(t_channel **chan, char *name)
{
  t_channel	*new;
  t_channel	*tmp;

  if ((new = malloc(sizeof(t_channel))) == NULL)
    exit(EXIT_FAILURE);
  strcpy(new->name, name);
  if (*chan == NULL)
    {
      *chan = new;
      return ;
    }
  tmp = *chan;
  while (tmp->next)
    tmp = tmp->next;
  tmp->next = new;
}

int		del_channel(t_channel **chan, char *name)
{
  t_channel	*tmp;
  t_channel	*save;

  tmp = *chan;
  if (!tmp)
    return (-1);
  if (!strcmp(tmp->name, name))
    {
      *chan = tmp->next;
      free(tmp);
      return (-1);
    }
  while (tmp->next)
    {
      if (!strcmp(tmp->next->name, name))
	{
	  save = tmp->next;
	  tmp->next = tmp->next->next;
	  free(save);
	  return (0);
	}
      tmp = tmp->next;
    }
  return (-1);
}

int		has_channel(t_channel **chan, char *name)
{
  t_channel	*tmp;

  tmp = *chan;
  while (tmp)
    {
      if (!strcmp(tmp->name, name))
	return (1);
      tmp = tmp->next;
    }
  return (0);
}
