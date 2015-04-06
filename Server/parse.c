#include <string.h>
#include "server.h"

int	get_prefixe(char *cmd, t_packet *pack)
{
  if (cmd[0] == ':')
    {
      pack->prefix = strndup(cmd + 1, strcspn(cmd, " "));
      return (0);
    }
  pack->prefix = NULL;
  return (1);
}

int	get_command(char *cmd, t_packet *pack, int *idx)
{
  if (!cmd)
    return (1);
  pack->command = strndup(cmd, strcspn(cmd, " "));
  if (idx)
    *idx = strcspn(cmd, " ");
  if (pack->command)
    return (0);
  return (1);
}

int	get_params(char *cmd, t_packet *packet)
{
  int	i;
  char	*arg;
  char	*cmda;

  i = 0;
  cmda = cmd;
  while ((arg = strtok(cmda, " ")))
    {
      packet->arg[i] = arg;
      if (cmda)
	cmda = NULL;
      ++i;
    }
  packet->arg[i] = NULL;
  packet->argn = i;
}

int	get_trailer(char *cmd, t_packet *packet)
{
  if (index(cmd, ':') == NULL)
    {
      packet->trailer = NULL;
      return (1);
    }
  packet->trailer = strdup(index(cmd, ':') + 1);
  index(cmd, ':')[0] = 0;
  if (packet->trailer)
    return (0);
  return (1);
}

int	fill_packet(char *cmd, t_packet *pack)
{
  int	idx;
  
  idx = 0;
  if (get_prefixe(cmd, pack) == 0)
    {
      cmd = index(cmd, ' ') + 1;
    }
  get_command(cmd, pack, &idx);
  printf("idx:%d\n", idx);
  get_trailer(&cmd[idx], pack);
  get_params(&cmd[idx], pack);
}

int main(int ac, char **av)
{
  t_packet lul;
  int i = 0;
  if (ac == 2)
    {
      fill_packet(av[1], &lul);
      printf("prefixe:%s \n command:%s \n trailer: %s \n", lul.prefix, lul.command, lul.trailer);
      printf("arguments:\n");
      for (i = 0;lul.arg[i] != NULL; i++)
	{
	  printf("arg%d: %s \n", i, lul.arg[i]);
	}
    }
}
