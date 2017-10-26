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

#include "my.h"
#include "defines.h"

int			connect_client(session_info_t *session)
{
  struct hostent	*info;
  struct sockaddr_in	serv_addr;

  mprintf("Connecting to %s ...\n", session->ip);
  info = gethostbyname(session->ip);
  session->csocket = socket(AF_INET, SOCK_DGRAM, 0);
  if (session->csocket == -1)
  {
    mdprintf(2, "Error : Could not create client socket\n");
    return (-1);
  }
  zeros((char *)&serv_addr, sizeof(serv_addr));
  if (info == NULL)
  {
    mdprintf(2, "Error : Could not resolve hostname %s\n", session->ip);
    return (-1);
  }
  serv_addr.sin_addr = *(struct in_addr *)info->h_addr;
  serv_addr.sin_port = htons(SERVER_PORT);
  serv_addr.sin_family = AF_INET;
  if (connect(session->csocket, (struct sockaddr *)&serv_addr,
	      sizeof(struct sockaddr)) == -1)
  {
    mdprintf(2, "Error : Could not connect to %s\n", session->ip);
    return (-1);
  }
  mprintf("Successfully connected to %s\n", session->ip);
  return (0);
}
