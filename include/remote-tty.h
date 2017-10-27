/*
** EPITECH PROJECT, 2017
** remote-tty
** File description:
** header
*/

#ifndef REMOTE_TTY_H_
# define REMOTE_TTY_H_

# include <pthread.h>
# include <termios.h>
# include <arpa/inet.h>

# define SERVER		(1)
# define CLIENT		(0)

# define USERNAME_FLAG	("-u")
# define IP_FLAG	("-ip")
# define PORT_FLAG	("-p")

# define PROMPT_CUR	(" > ")

# define MEM_ERROR	("Error : Not enough memory\n")

# define STATUS_OK	(0)
# define ACCEPT_FAILED	(-1)
# define COM_ERROR	(-2)

# define CON_TIMEOUT	(2)

# define NB_FCTION	(5)
# define NB_CMDS        (4)

# define RETURN_FILE	(".remote-tty")

struct		session_info_s
{
  char		*command;
  char		*color;
  char		*username;
  int		side;
  int		port;
  char		*ip;
  int		socket;
  int		csocket;
  pthread_t	thread;
  int		status;
};

struct                  header_s
{
  int                   action;
  int                   pktlen;
};

struct          rcv_ptr_tab_s
{
  int           action;
  int           (* fction)(struct session_info_s *session,
			    struct header_s *header);
};

struct		cmd_ptr_tab_s
{
  const char	*action;
  int		(* fction)(const char *cmd,
			   struct session_info_s *session);
};

typedef struct cmd_ptr_tab_s cmd_ptr_tab_t;
typedef struct header_s header_t;
typedef struct session_info_s session_info_t;
typedef struct rcv_ptr_tab_s rcv_ptr_tab_t;

int	start_session(session_info_t *session, int ac, char **av);
int	end_session(session_info_t *session, struct termios *old);
int	start_communication(session_info_t *session);
int	start_server(session_info_t *session);
int	start_server_thread(session_info_t *session);
int	connect_client(session_info_t *session);
int	init_return_fd(void);

void	prompt(void);

int	receive(session_info_t *session);
int	receive_welcome(session_info_t *session, header_t *header);
int	receive_msg(session_info_t *session, header_t *header);
int	send_msg(session_info_t *session, int action, char *msg);
int	receive_leave(session_info_t *session, header_t *header);
int	receive_command(session_info_t *session, header_t *header);
int	send_return_fd(session_info_t *session, int fd);
int	receive_command_return(session_info_t *session, header_t *header);

int	accept_command(const char *cmd, session_info_t *session);
int	user_command(const char *cmd, session_info_t *session);
int	cmd_quit(const char *cmd, session_info_t *session);
int	set_color(const char *cmd, session_info_t *session);
int	send_command_request(const char *cmd, session_info_t *session);
int	display_command(const char *cmd, session_info_t *session);

int	encrypt(char *msg, int pktlen);
int	unencrypt(char *msg, int pktlen);

#endif /* !REMOTE_TTY_H_ */
