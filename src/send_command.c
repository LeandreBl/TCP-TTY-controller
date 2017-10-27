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
#include "colors.h"

static int	isacmd(const char *cmd)
{
  if (my_strlen(cmd) < 6)
    return (0);
  return (1);
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
  epur_str(session->command);
  mprintf("\r%s %sask to execute %s: %s%s%s\nType !accept to execute it\n",
	  session->command, BOLDGREEN, RESET, BOLDWHITE,
	  session->command + my_strlen(session->command) + 1, RESET);
  my_strcpy(session->command, session->command + my_strlen(session->command) + 1);
  prompt();
  return (0);
}

int		send_command_request(const char *cmd, session_info_t *session)
{
  if (!isacmd(cmd))
  {
    mdprintf(2, "\rDoes not seem like a valid command\n");
    prompt();
    return (-1);
  }
  cmd += 5;
  if (send_msg(session, RQ_COMMAND, (char *)cmd) == -1)
    return (-1);
  return (0);
}
