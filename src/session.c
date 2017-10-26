/*
** EPITECH PROJECT, 2017
** remote-tty
** File description:
** session info start / end
*/

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#include "my.h"
#include "defines.h"

#include "remote-tty.h"

static int	change_username(session_info_t *session, const char *arg)
{
  sfree(&session->username);
  session->username = my_strdup(arg);
  if (session->username == NULL)
  {
    mdprintf(2, MEM_ERROR);
    return (-1);
  }
  return (0);
}

static int	change_ip(session_info_t *session, const char *arg)
{
  sfree(&session->ip);
  session->ip = my_strdup(arg);
  if (session->ip == NULL)
  {
    mdprintf(2, MEM_ERROR);
    return (-1);
  }
  return (0);
}

static int	change_side(session_info_t *session, const char *arg)
{
  if (my_strcmp(arg, "server") == 0)
    session->side = SERVER;
  if (my_strcmp(arg, "client") == 0)
    session->side = CLIENT;
  return (0);
}

int		start_session(session_info_t *session, int ac, char **av)
{
  int		i;

  i = 0;
  session->username = NULL;
  session->side = SERVER;
  session->ip = NULL;
  session->status = STATUS_OK;
  session->csocket = -1;
  session->socket = -1;
  while (i < ac)
  {
    if (my_strcmp(av[i], USERNAME_FLAG) == 0 && av[i + 1])
      if (change_username(session, av[i + 1]) == -1)
	return (-1);
    if (my_strcmp(av[i], IP_FLAG) == 0 && av[i + 1])
      if (change_ip(session, av[i + 1]) == -1)
	return (-1);
    if (my_strcmp(av[i], SIDE_FLAG) == 0 && av[i + 1])
      if (change_side(session, av[i + 1]) == -1)
	return (-1);
    ++i;
  }
  if (session->username == NULL)
  {
    session->username = my_strdup(getenv("USER"));
    if (session->username == NULL)
      return (-1);
  }
  return (0);
}

int		end_session(session_info_t *session, struct termios *old)
{
  mprintf("\nEnding session of : %s\n", session->username);
  if (tcsetattr(0, TCSANOW, old) == -1)
    mdprintf(2, "Error : Could not reset term configs\n");
  sfree(&session->username);
  sfree(&session->ip);
  if ((session->socket > 0 && close(session->socket) == -1) ||
      (session->csocket > 0 && close(session->csocket) == -1))
  {
    mdprintf(2, "Error : Could not close socket\n");
    return (-1);
  }
  mprintf("Waiting for threads to end : ");
  kill(getpid(), SIGUSR1);
  if (pthread_cancel(session->rthread) == -1 ||
      pthread_cancel(session->sthread) == -1 ||
      pthread_join(session->rthread, NULL) == -1 ||
      pthread_join(session->sthread, NULL) == -1)
    {
    mdprintf(2, "Error : Could not cancel or stop the server thread\n");
    return (-1);
  }
  mprintf("Done\n");
  return (0);
}
