/*
** EPITECH PROJECT, 2017
** remote-tty
** File description:
** receive cmd
*/

#include <unistd.h>

#include "remote-tty.h"
#include "protocol.h"

#include "my.h"
#include "defines.h"
#include "colors.h"

int		receive_command_return(session_info_t *session, header_t *header)
{
  char		*msg;

  msg = my_calloc(header->pktlen + 1);
  if (msg == NULL)
    return (-1);
  if (read(session->csocket, msg, header->pktlen) == -1)
  {
    mdprintf(2, "Error : Could not receive mesasge from %s\n", session->ip);
    return (-1);
  }
  unencrypt(msg, header->pktlen);
  mprintf("\r -%s%s : %sReturn command :\n%s%s", msg, RESET, BOLDGREEN, msg + my_strlen(msg) + 1, RESET);
  prompt();
  sfree(&msg);
  return (0);
}
