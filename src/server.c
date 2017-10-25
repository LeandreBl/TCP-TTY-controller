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

#include "my.h"
#include "defines.h"

int			start_server(session_info_t *session)
{
  struct sockaddr_in	serv_addr;

  session->socket = socket(AF_INET, SOCK_STREAM, 0);
  if (session->socket == -1)
  {
    mdprintf(2, "Error : Could not create server's socket\n");
    return (-1);
  }
  zeros((char *)&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(SERVER_PORT);
  if (bind(session->socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
  {
    mdprintf(2, "Error : Could not bind sockaddr with server socket\n");
    return (-1);
  }
  start_server_thread(session);
  return (0);
}
