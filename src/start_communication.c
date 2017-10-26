/*
** EPITECH PROJECT, 2017
** remote-tty
** File description:
** start_communication
*/

#include "remote-tty.h"

#include "my.h"
#include "defines.h"

static int	start_threads(session_info_t *session)
{
  if (session->side == SERVER &&
      (start_server(session) == -1 || start_client_thread(session) == -1))
    return (-1);
  if (session->side == CLIENT &&
      (connect_client(session) == -1 || start_client_thread(session) == -1
       || start_server_thread(session) == -1))
      return (-1);
  return (0);
}

int		start_communication(session_info_t *session)
{
  char		*line;
  char		**cmds;

  routine_ioctl();
  cmds = NULL;
  if (start_threads(session) == -1)
    return (-1);
  while ((line = get_cmd(cmds, " > ")) != NULL)
  {
    cmds = tab_append(cmds, line);
  }
  free_tab(cmds);
  return (0);
}
