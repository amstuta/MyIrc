/*
** server.h for server in /home/amstuta/rendu/PSU_2014_myirc/Server
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Fri Mar 27 15:30:08 2015 arthur
** Last update Fri Apr  3 12:18:48 2015 arthur
*/

#ifndef SERVER_H_
# define SERVER_H_
# define LINE_SIZE	4096

# include <sys/select.h>

typedef void(*function)(int, char*);

typedef struct		s_client
{
  int			fd;
  char			*login;
  char			*channel;
  struct s_client	*next;
}			t_client;

typedef struct		s_channel
{
  char			*name;
  struct s_channel	*next;
}			t_channel;

typedef struct		s_packet
{
  char			*prefix;
  char			*command;
  char			*arg[256];
  char			*trailer;
  int			argn;
}			t_packet;

void			exit_signal(int);
void			add_client(int, char*);
void			remove_client(int);
void			accept_client(int);
void			set_clients(fd_set*, fd_set*);
t_client		*init_clients(int);
void			check_clients_fd_in(fd_set*);
void			check_clients_fd_out(fd_set*);
void			my_select(int);
int			get_bigger_fd();
void			read_client(int);
void			add_channel(char*);
void			list_channels(int);
void			search_channels(int, char*);
int			channel_exists(char*);
char			*get_client_channel(int);
void			exec_cmd(int, char*);
char			*get_args(char*);
int			get_idx_cmd(char*);
void			nick(int, char*);
void			list(int, char*);
void			join(int, char*);
void			part(int, char*);
void			users(int, char*);
void			msg(int, char*);
void			send_file(int, char*);
void			accept_file(int, char*);
void			send_msg_all(int, char*);
int			get_user_fd(char*);
char			*get_login_from_fd(int);

extern t_client		*g_clients;
extern t_channel	*g_channels;

#endif /* !SERVER_H_ */
