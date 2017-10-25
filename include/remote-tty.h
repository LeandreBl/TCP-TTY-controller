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

# define SERVER		(1)
# define CLIENT		(0)

# define USERNAME_FLAG	("-u")
# define IP_FLAG	("-ip")
# define SIDE_FLAG	("-set")

# define MEM_ERROR	("Error : Not enough memory\n")

struct		session_info_s
{
  char		*username;
  int		side;
  char		*ip;
  int		socket;
  pthread_t	com_thread;
};

typedef struct session_info_s session_info_t;

int	start_session(session_info_t *session, int ac, char **av);
int	end_session(session_info_t *session, struct termios *old);
int	start_communication(session_info_t *session);

#endif /* !REMOTE_TTY_H_ */
