/*
** EPITECH PROJECT, 2017
** remote-tty
** File description:
** start_communication
*/

#include "remote-tty.h"

#include "my.h"
#include "defines.h"

static int	server_thread(session_info_t *session)
{
  session->com_thread = session->com_thread;
  return (0);
}

int		start_communication(session_info_t *session)
{
  char		*line;
  char		**cmds;

  routine_ioctl();
  cmds = NULL;
  server_thread(session);
  while ((line = get_cmd(cmds, " > ")) != NULL)
  {
    cmds = tab_append(cmds, line);
  }
  free_tab(cmds);
  return (0);
}
