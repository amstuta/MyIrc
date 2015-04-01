/*
** server.h for server in /home/amstuta/rendu/PSU_2014_myirc/Server
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Fri Mar 27 15:30:08 2015 arthur
** Last update Fri Mar 27 17:06:48 2015 arthur
*/

#ifndef SERVER_H_
# define SERVER_H_

# define LINE_SIZE	4096

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

void		exit_signal(int);
void		add_client(t_client**, int, char*);
void		remove_client(t_client**, int);
void		accept_client(int, t_client**);
void		set_clients(t_client**, fd_set*);
t_client	*init_clients(int);
void		check_clients_fd(t_client*, fd_set*);
void		my_select(int);
int		get_bigger_fd(t_client*);
void		read_client(int, t_client*);
void		add_channel(t_channel**, char*);
void		list_channels(t_channel*, int);

#endif /* !SERVER_H_ */
