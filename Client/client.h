/*
** client.h for client in /home/amstuta/rendu/PSU_2014_myirc/Client
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Fri Mar 27 16:04:16 2015 arthur
** Last update Fri Mar 27 16:39:15 2015 arthur
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
int	check_cmd(char*);
int	create_socket(char*, int);
void	connect_to_serv(char*);

#endif
