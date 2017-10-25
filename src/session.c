/*
** EPITECH PROJECT, 2017
** remote-tty
** File description:
** session info start / end
*/

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
  sfree(&session->username);
  sfree(&session->ip);
  tcsetattr(0, TCSANOW, old);
  return (0);
}
