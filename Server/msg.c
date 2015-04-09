#include <string.h>
#include <unistd.h>
#include "server.h"

void	send_msg(int fd, char *msg)
{
  char	buff[LINE_SIZE];

  strcpy(buff, msg);
  strcat(buff, END);
  write(fd, buff, strlen(buff));
}
