/*
** client.h for client in /home/amstuta/rendu/PSU_2014_myirc/Client
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Fri Mar 27 16:04:16 2015 arthur
** Last update Wed Apr  8 11:07:51 2015 arthur
*/

#ifndef CLIENT_H_
# define CLIENT_H_
# define LINE_SIZE	4096
# define SERVER		"/server"
# define NICK		"/nick"
# define LIST		"/list"
# define JOIN		"/join"
# define PART		"/part"
# define USERS		"/users"
# define MSG		"/msg"
# define SEND		"/send_file"
# define ACCEPT		"/accept_file"

void	read_cmd();
void	select_entry(int);
void	read_cmd_serv(int);
void	read_cmd_str(int);
int	create_socket(char*, int);
int	connect_to_serv(char*);
int	check_cmd(char*);

#endif
