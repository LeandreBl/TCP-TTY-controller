/*
** EPITECH PROJECT, 2017
** remote-tty
** File description:
** msg
*/

#include <unistd.h>

#include "protocol.h"
#include "remote-tty.h"

#include "my.h"
#include "defines.h"
#include "colors.h"

int		send_msg(session_info_t *session, int action, char *msg)
{
  int		magic;
  header_t	header;
  char		*send;

  magic = MAGIC_NUMBER;
  header.action = action;
  send = catalloc("%s%s-%s", session->color, session->username, msg);
  header.pktlen = my_strlen(send);
  if (send == NULL)
    return (-1);
  send[my_strlen(session->username) + my_strlen(session->color)] = 0;
  encrypt(send, header.pktlen);
  if (write(session->csocket, &magic, sizeof(int)) == -1 ||
      write(session->csocket, &header, sizeof(header_t)) == -1 ||
      write(session->csocket, send, header.pktlen) == -1)
  {
    mdprintf(2, "Error : Could not send message\n");
    session->status = COM_ERROR;
    sfree(&send);
    return (-1);
  }
  sfree(&send);
  return (0);
}

int		receive_msg(session_info_t *session, header_t *header)
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
  mprintf("\r %s : %s%s\n > ", msg, msg + my_strlen(msg) + 1, RESET);
  sfree(&msg);
  return (0);
}
