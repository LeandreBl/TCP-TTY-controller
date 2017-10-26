/*
** EPITECH PROJECT, 2017
** remote-tty
** File description:
** exec remote command
*/

#include <stdlib.h>
#include <unistd.h>

#include "remote-tty.h"
#include "protocol.h"

#include "my.h"
#include "defines.h"

static int	isacmd(const char *cmd)
{
  if (my_strlen(cmd) < 6)
    return (0);
  return (1);
}

int		accept_command(const char *cmd, session_info_t *session)
{
  if (my_strcmp(cmd, "!accept"))
  {
    mprintf("\rOnly type !accept\n");
    return (-1);
  }
  system(session->command);
  return (0);
}

int		receive_command(session_info_t *session, header_t *header)
{
  sfree(&session->command);
  session->command = my_calloc(header->pktlen + 1);
  if (session->command == NULL)
    return (-1);
  if (read(session->csocket, session->command, header->pktlen) == -1)
  {
    mdprintf(2, "Error : Could not receive message from %s\n", session->ip);
    return (-1);
  }
  unencrypt(session->command, header->pktlen);
  shift_left(session->command, my_strlen("exec "));
  epur_str(session->command);
  return (0);
}

int		send_command_request(const char *cmd, session_info_t *session)
{
  if (!isacmd(cmd))
  {
    mdprintf(2, "\rDoes not seem like a valid command\n");
    return (-1);
  }
  if (send_msg(session, RQ_COMMAND, (char *)cmd + 5) == -1)
    return (-1);
  return (0);
}
