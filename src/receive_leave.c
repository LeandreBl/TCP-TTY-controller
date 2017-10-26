/*
** EPITECH PROJECT, 2017
** remote-tty
** File description:
** leave msg
*/

#include <unistd.h>

#include "protocol.h"
#include "remote-tty.h"

#include "my.h"
#include "defines.h"

int		receive_leave(session_info_t *session, header_t *header)
{
  char		*msg;

  msg = my_calloc(header->pktlen + 1);
  if (msg == NULL)
    return (-1);
  if (read(session->csocket, msg, header->pktlen) == -1)
  {
    mdprintf(2, "Error : Could not receive message from %s\n", session->ip);
    return (-1);
  }
  unencrypt(msg, header->pktlen);
  mprintf("\r -%s left the chat\n", msg);
  sfree(&msg);
  close(session->csocket);
  close(session->socket);
  session->csocket = -1;
  session->socket = -1;
  return (0);
}
