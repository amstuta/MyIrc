/*
** client.h for client in /home/amstuta/rendu/PSU_2014_myirc/Client
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Fri Mar 27 16:04:16 2015 arthur
** Last update Sun Apr 12 21:38:23 2015 elkaim raphael
*/

#ifndef CLIENT_H_
# define CLIENT_H_
# define LINE_SIZE	4096
# define SERVER		"/server"
# define NICK		"NICK"
# define LIST		"LIST"
# define JOIN		"JOIN"
# define PART		"PART"
# define USERS		"NAMES"
# define MSG		"PRIVMSG"

typedef struct		s_packet
{
  char			*prefix;
  char			*command;
  char			*arg[256];
  char			*trailer;
  int			argn;
}			t_packet;

typedef void(*function)(char *, int);
typedef void(*function2)(t_packet *, int);

void	read_cmd();
void	select_entry(int);
int	read_cmd_serv(int);
int	read_cmd_str(int);
int	create_socket(char *, int);
int	connect_to_serv(char *);
int	check_cmd(char *);
void	exec_cmd(char *, int);
void	exec_cmd_srv(char *);
void	nick(char *, int);
void	users(char *, int);
void	msg(char *, int);
void	chanmsg(char *, int);
void	join(char *, int);
void	part(char *, int);
void	list(char *, int);
void	send_msg(int, char *);
int	fill_packet(char *, t_packet *);
void	sjoin(t_packet *, int);
void	spart(t_packet *, int);
void	smsg(t_packet *, int);
void	squit(t_packet *, int);

#endif
