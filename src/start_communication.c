/*
** EPITECH PROJECT, 2017
** remote-tty
** File description:
** start_communication
*/

#include "remote-tty.h"
#include "protocol.h"

#include "my.h"
#include "defines.h"

static int	start_threads(session_info_t *session)
{
  if (session->side == SERVER && start_server(session) == -1)
    return (-1);
  if (session->side == CLIENT && ((connect_client(session) == -1)
      || start_server_thread(session) == -1))
      return (-1);
  return (0);
}

static int	start_transmission(session_info_t *session)
{
  routine_ioctl();
  if (start_threads(session) == -1)
    return (-1);
  if (session->side == CLIENT && send_msg(session, WELCOME, NULL) == -1)
      return (-1);
  return (0);
}

int		start_communication(session_info_t *session)
{
  char		*line;
  char		**cmds;

  cmds = NULL;
  if (start_transmission(session) == -1)
    return (-1);
  while ((line = get_cmd(cmds, PROMPT_CUR)) != NULL)
  {
    if (line[0] == '!' && user_command(line + 1, session) == 1)
      break;
    else if (line[0] != '!' && line[0] != 0)
    {
      if (send_msg(session, SIMPLE_MSG, line) == -1)
	mprintf("Error : communication\n");
    }
    cmds = tab_append(cmds, line);
  }
  sfree(&line);
  send_msg(session, LEAVE, NULL);
  free_tab(cmds);
  return (0);
}
