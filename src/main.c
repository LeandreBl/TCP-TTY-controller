/*
** EPITECH PROJECT, 2017
** remote-tty
** File description:
** main
*/

#include <signal.h>

#include "my.h"
#include "defines.h"

#include "remote-tty.h"

static void		info_session(session_info_t *session)
{
  mprintf("Session username : %s\n", session->username);
  mprintf("Session set as : ");
  if (session->side == CLIENT)
    mprintf("client\n");
  if (session->side == SERVER)
    mprintf("server\n");
  mprintf("Try to connect on port : %d\n", session->port);
  if (session->side == SERVER)
    session->ip = get_ip(NULL);
  if (session->ip == NULL)
    mprintf("Error : Are you connected to internet ?\n");
  else
    mprintf("Server ip : %s\n", session->ip);
  mprintf("\n");
}

static int		get_old_conf(struct termios *old)
{
  mprintf("Saving terminal configs : ");
  if (tcgetattr(0, old) == -1)
  {
    mprintf("Error\n");
    mdprintf(2, "Error : Could not save the terminal configs\n");
    return (-1);
  }
  mprintf("Done\n");
  return (0);
}

static void		sig_handler(__attribute__ ((unused)) int sig)
{
}

int			main(int ac, char **av)
{
  session_info_t	session;
  struct termios	old;

  if (start_session(&session, ac, av) == -1)
  {
    mdprintf(2, "Error : Unable to start the session\n");
    return (-1);
  }
  if (get_old_conf(&old) == -1)
    return (-1);
  signal(SIGUSR1, sig_handler);
  signal(SIGPIPE, sig_handler);
  info_session(&session);
  if (start_communication(&session) == -1)
    mdprintf(2, "Error : Communication error\n");
  if (end_session(&session, &old) == -1)
  {
    mdprintf(2, "Error : Failed to end the session properly\n");
    return (-1);
  }
  return (0);
}
