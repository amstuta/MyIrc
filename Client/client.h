/*
** client.h for client in /home/amstuta/rendu/PSU_2014_myirc/Client
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Fri Mar 27 16:04:16 2015 arthur
** Last update Wed Apr  8 13:59:35 2015 arthur
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
# define SEND		"SF"
# define ACCEPT		"AF"

void	read_cmd();
void	select_entry(int);
void	read_cmd_serv(int);
void	read_cmd_str(int);
int	create_socket(char*, int);
int	connect_to_serv(char*);
int	check_cmd(char*);

#endif
