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

int		send_header(session_info_t *session, int action, int size)
{
  int		magic;
  header_t	header;

  magic = MAGIC_NUMBER;
  header.action = action;
  header.pktlen = size;
  if (write(session->csocket, &magic, sizeof(int)) == -1 ||
      write(session->csocket, &header, sizeof(header_t)) == -1)
  {
    mdprintf(2, "Error : Could not send packet\n");
    prompt();
    session->status = COM_ERROR;
    return (-1);
  }
  return (0);
}

int		send_msg(session_info_t *session, int action, char *msg)
{
  char		*send;
  int		size;

  send = catalloc("%s%s-%s", session->color, session->username, msg);
  if (send == NULL)
    return (-1);
  size = my_strlen(send);
  if (send_header(session, action, size) == -1)
  {
    sfree(&send);
    return (-1);
  }
  send[my_strlen(session->username) + my_strlen(session->color)] = 0;
  encrypt(send, size);
  if (write(session->csocket, send, size) == -1)
  {
    mdprintf(2, "Error : Could not send message\n");
    prompt();
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
    prompt();
    return (-1);
  }
  unencrypt(msg, header->pktlen);
  mprintf("\r %s %s: %s%s%s%s\n", msg, BOLDWHITE, RESET, WHITE, msg + my_strlen(msg) + 1, RESET);
  prompt();
  sfree(&msg);
  return (0);
}
