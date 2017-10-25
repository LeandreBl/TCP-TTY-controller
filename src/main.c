/*
** EPITECH PROJECT, 2017
** remote-tty
** File description:
** main
*/

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
  if (session->ip != NULL)
    mprintf("Connecting to : %s\n", session->ip);
  else
  {
    session->ip = get_ip(NULL);
    if (session->ip == NULL)
      mprintf("Error : Are you connected to internet ?\n");
    else
      mprintf("Server ip : %s\n", session->ip);
  }
  mprintf("\n");
}

int			main(int ac, char **av)
{
  session_info_t	session;

  if (start_session(&session, ac, av) == -1)
  {
    mdprintf(2, "Error : Unable to start the session\n");
    return (-1);
  }
  info_session(&session);
  if (end_session(&session) == -1)
  {
    mdprintf(2, "Error : Failed to end the session properly\n");
    return (-1);
  }
  return (0);
}
