#include <string.h>
#include <unistd.h>
#include "client.h"

void	send_msg(int fd, char *cmd)
{
  char	buff[4096];

  strcpy(buff, cmd);
  strcat(buff, "\r\n");
  write(fd, buff, strlen(buff));
}
