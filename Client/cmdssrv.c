/*
** cmdssrv.c for irc in /home/elkaim_r/projects/c/PSU_2014_myirc/Client
** 
** Made by elkaim raphael
** Login   <elkaim_r@epitech.net>
** 
** Started on  Sun Apr 12 21:29:15 2015 elkaim raphael
** Last update Sun Apr 12 21:50:20 2015 elkaim raphael
*/

#include <stdio.h>
#include "client.h"

void	smsg(t_packet *res, int fd)
{
  (void)fd;
  printf("\r %s |: %s \n", res->prefix, res->trailer);
}

void	sjoin(t_packet *res, int fd)
{
  (void)fd;
  printf("\r %s joined %s \n", res->prefix, res->trailer);
}

void	spart(t_packet *res, int fd)
{
  (void)fd;
  printf("\r %s left %s \n", res->prefix, res->trailer);
}

void	squit(t_packet *res, int fd)
{
  (void)fd;
  printf("\r %s left the server.\n", res->prefix);
}
