/*
** EPITECH PROJECT, 2017
** remote-tty
** File description:
** session info start
*/

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#include "my.h"
#include "defines.h"

#include "remote-tty.h"
#include "protocol.h"

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
  session->side = CLIENT;
  return (0);
}

static int	set_session(session_info_t *session)
{
  session->command = NULL;
  session->username = NULL;
  session->side = SERVER;
  session->ip = NULL;
  session->status = STATUS_OK;
  session->csocket = -1;
  session->socket = -1;
  session->color = NULL;
  session->port = SERVER_PORT;
  return (0);
}

int		start_session(session_info_t *session, int ac, char **av)
{
  int		i;

  i = 0;
  if (set_session(session) == -1)
    return (-1);
  while (i < ac)
  {
    if (my_strcmp(av[i], USERNAME_FLAG) == 0 && av[i + 1])
      if (change_username(session, av[i + 1]) == -1)
	return (-1);
    if (my_strcmp(av[i], IP_FLAG) == 0 && av[i + 1])
      if (change_ip(session, av[i + 1]) == -1)
	return (-1);
    if (my_strcmp(av[i], PORT_FLAG) == 0 && av[i + 1])
      if ((session->port = my_getnbr(av[i + 1])) <= 0)
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
