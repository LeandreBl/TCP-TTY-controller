/*
** EPITECH PROJECT, 2017
** remote-tty
** File description:
** send welcome
*/

#include <unistd.h>

#include "protocol.h"
#include "remote-tty.h"

#include "my.h"
#include "defines.h"

int		receive_welcome(session_info_t *session, header_t *header)
{
  char		*name;

  name = my_calloc(header->pktlen + 1);
  if (read(session->csocket, name, header->pktlen) == -1)
  {
    session->status = COM_ERROR;
    return (-1);
  }
  mprintf("\r%S joined the chat\n > ", name);
  return (0);
}
