/*
** EPITECH PROJECT, 2017
** remote-tty
** File description:
** start_communication
*/

#include "remote-tty.h"

#include "my.h"
#include "defines.h"

int		start_communication(session_info_t *session)
{
  char		*line;
  char		**cmds;

  routine_ioctl();
  cmds = NULL;
  session->socket = -1;
  while ((line = get_cmd(cmds, " > ")) != NULL)
  {
    cmds = tab_append(cmds, line);
  }
  free_tab(cmds);
  return (0);
}
