/*
** server.h for server in /home/amstuta/rendu/PSU_2014_myirc/Server
**
** Made by arthur
** Login   <amstuta@epitech.net>
**
** Started on  Fri Mar 27 15:30:08 2015 arthur
** Last update Wed Apr  8 17:56:19 2015 elkaim raphael
*/

#ifndef SERVER_H_
# define SERVER_H_
# define LINE_SIZE	4096

# include <sys/select.h>

typedef enum
  {
    true, 
    false
  }			e_bool;

typedef struct		s_cmd
{
  char			com[LINE_SIZE];
  e_bool		in_out;
  struct s_cmd		*next;
}			t_cmd;

typedef struct		s_client
{
  int			fd;
  char			login[256];
  char			channel[256];
  t_cmd			*cmd_in;
  t_cmd			*cmd_out;
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

typedef void(*function)(int, t_packet *);

void			exit_signal(int);
void			add_client(int, char*);
void			remove_client(int);
void			accept_client(int);
void			set_clients(fd_set*, fd_set*);
t_client		*init_clients(int);
void			check_clients_fd_in(fd_set*, t_client *);
void			check_clients_fd_out(fd_set*);
void			my_select(int);
int			get_bigger_fd();
int			read_client(t_client *);
void			add_channel(char*);
void			list_channels(int);
void			search_channels(int, char*);
int			channel_exists(char*);
char			*get_client_channel(int);
void			exec_cmd(t_client *);
char			*get_args(char*);
int			get_idx_cmd(char*);
void			nick(int, t_packet *);
void			list(int, t_packet *);
void			join(int, t_packet *);
void			part(int, t_packet *);
void			users(int, t_packet *);
void			msg(int, t_packet *);
void			send_file(int, t_packet *);
void			accept_file(int, t_packet *);
void			send_msg_all(int, char *);
int			get_user_fd(char*);
char			*get_login_from_fd(int);
void			add_command(t_cmd**, char*, e_bool);
void			remove_command(t_cmd**, t_cmd*);
void			command_to_list(char*, t_cmd**);
void			write_reps(int, t_cmd**);
int			get_prefixe(char *, t_packet *);
int			get_command(char *, t_packet *, int *);
int			get_params(char *, t_packet *);
int			get_trailer(char *, t_packet *);
int			fill_packet(char *, t_packet *);

extern t_client		*g_clients;
extern t_channel	*g_channels;

#endif /* !SERVER_H_ */
