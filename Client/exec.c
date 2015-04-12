#include <string.h>
#include "client.h"

int			get_idx_cmd(char *cmd)
{
  int			i;
  static const char	*tab[7] = {
    "/join", "/part", "/msg",
    "/users", "/nick", "/list", NULL
  };

  i = 0;
  while (tab[i])
    {
      if (!strncmp(cmd, tab[i], strlen(tab[i])))
	return (i);
      ++i;
    }
  return (-1);
}

void			exec_cmd(char *cmd, int fd)
{
  int			idx;
  //t_cmd			*tmp;
  //t_packet		res;
  static function	tab[6] = {
    &join, &part, &msg, &users, &nick,
    &list
  };

  //tmp = cli->cmd_in;
      //fill_packet(tmp->com, &res);
  if ((idx = get_idx_cmd(cmd)) == -1)
    chanmsg(cmd, fd);
  else
    tab[idx](cmd, fd);
  //tmp = tmp->next;
}
