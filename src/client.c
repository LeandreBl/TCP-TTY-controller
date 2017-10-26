/*
** EPITECH PROJECT, 2017
** remote-tty
** File description:
** client
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "remote-tty.h"
#include "protocol.h"

#include "my.h"
#include "defines.h"

static void		fill_serv_addr(struct sockaddr_in *serv_addr,
				       struct hostent *info,
				       int port)
{
  zeros((char *)serv_addr, sizeof(*serv_addr));
  serv_addr->sin_addr = *(struct in_addr *)info->h_addr;
  serv_addr->sin_port = htons(port);
  serv_addr->sin_family = AF_INET;
}

int			connect_client(session_info_t *session)
{
  struct hostent	*info;
  struct sockaddr_in	serv_addr;

  mprintf("Connecting to %s ...\n", session->ip);
  info = gethostbyname(session->ip);
  if (info == NULL)
  {
    mdprintf(2, "Error : Could not resolve hostname %s\n", session->ip);
    return (-1);
  }
  session->csocket = socket(AF_INET, SOCK_STREAM, 0);
  if (session->csocket == -1)
  {
    mdprintf(2, "Error : Could not create client socket\n");
    return (-1);
  }
  fill_serv_addr(&serv_addr, info, session->port);
  if (connect(session->csocket, (struct sockaddr *)&serv_addr,
	      sizeof(struct sockaddr)) == -1)
  {
    mdprintf(2, "Error : Could not connect to %s\n", session->ip);
    return (-1);
  }
  mprintf("Successfully connected to %s\n", session->ip);
  return (0);
}
