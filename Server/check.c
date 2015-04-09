#include <ctype.h>
#include "server.h"

int		check_nick(char *nick, int fd)
{
  t_client	*tmp;
  char		buff[LINE_SIZE];

  tmp = g_client->next;
  memset(buff, 0, LINE_SIZE);
  if (strlen(nick) > 9 || !is_alnum(nick))
    {
      send_msg(fd, strcat(strcat(strcat(buff, "432 "), nick), ":Erroneus Nickname")); //norme
      return (1);
    }
  while (tmp)
    {
      if (!strcmp(tmp->login, nick))
	{
	  send_msg(fd, strcat(strcat(buff, "433 "), nick));
	  return (1);
	}
      tmp = tmp->next;
    }
  return (0);
}
