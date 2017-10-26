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

# define SERVER_PORT	(14344)

# define USERNAME_FLAG	("-u")
# define IP_FLAG	("-ip")
# define SIDE_FLAG	("-set")

# define MEM_ERROR	("Error : Not enough memory\n")

# define STATUS_OK	(0)
# define ACCEPT_FAILED	(-1)
# define COM_ERROR	(-2)

# define CON_TIMEOUT	(5)

# define NB_FCTION	(3)

struct		session_info_s
{
  char		*username;
  int		side;
  char		*ip;
  int		socket;
  int		csocket;
  pthread_t	sthread;
  pthread_t	rthread;
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

typedef struct header_s header_t;
typedef struct session_info_s session_info_t;
typedef struct rcv_ptr_tab_s rcv_ptr_tab_t;

int	start_session(session_info_t *session, int ac, char **av);
int	end_session(session_info_t *session, struct termios *old);
int	start_communication(session_info_t *session);
int	start_server(session_info_t *session);
int	start_server_thread(session_info_t *session);
int	connect_client(session_info_t *session);
int	start_client_thread(session_info_t *session);

int	receive(session_info_t *session);
int	receive_welcome(session_info_t *session, header_t *header);
int	receive_msg(session_info_t *session, header_t *header);
int	send_msg(session_info_t *session, int action, char *msg);
int	receive_leave(session_info_t *session, header_t *header);

#endif /* !REMOTE_TTY_H_ */
