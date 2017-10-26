/*
** EPITECH PROJECT, 2017
** remote-tty
** File description:
** server side
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "remote-tty.h"
#include "protocol.h"

#include "my.h"
#include "defines.h"

int			start_server(session_info_t *session)
{
  struct sockaddr_in	sin;

  session->socket = socket(AF_INET, SOCK_STREAM, 0);
  if (session->socket == -1)
  {
    mdprintf(2, "Error : Could not create server's socket\n");
    return (-1);
  }
  zeros((char *)&sin, sizeof(sin));
  sin.sin_addr.s_addr = INADDR_ANY;
  sin.sin_family = AF_INET;
  sin.sin_port = htons(session->port);
  if (bind(session->socket, (struct sockaddr *)&sin,
	   sizeof(struct sockaddr_in)) == -1)
  {
    session->socket = -1;
    mdprintf(2, "Error : Could not bind sockaddr with server socket\n");
    return (-1);
  }
  start_server_thread(session);
  return (0);
}
