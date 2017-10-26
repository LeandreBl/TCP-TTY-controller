/*
** EPITECH PROJECT, 2017
** remote-tty
** File description:
** server thread
*/

#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "remote-tty.h"

#include "my.h"
#include "defines.h"

static int		accept_new_client(session_info_t *session)
{
  socklen_t		clilen;
  struct sockaddr_in	csin;

  mprintf("\rWaiting for new client : ");
  if (listen(session->socket, 5) == -1)
  {
    mdprintf(2, "Error : Could not listen on port %d\n", SERVER_PORT);
    return (-1);
  }
  clilen = sizeof(csin);
  session->csocket = accept(session->socket,
				  (struct sockaddr *)&csin, &clilen);
  if (session->csocket == -1)
  {
    mdprintf(2, "Error : Could not accept the connection of the client\n");
    return (-1);
  }
  mprintf("\n%s client is now connected.\n", inet_ntoa(csin.sin_addr));
  return (0);
}

static void		receive_thread(session_info_t *session)
{
  if (session->side == SERVER && accept_new_client(session) == -1)
  {
    session->status = ACCEPT_FAILED;
    return;
  }
  while (session->status == STATUS_OK)
  {
    if (session->csocket == -1 && session->side == SERVER)
      if (accept_new_client(session) == -1)
	session->status = ACCEPT_FAILED;
  }
}

int			start_server_thread(session_info_t *session)
{
  if (pthread_create(&session->rthread, NULL,
		     (void *)receive_thread, (void *)session) == -1)
  {
    mdprintf(2, "Error : Could not start receive thread\n");
    return (-1);
  }
  if (pthread_detach(session->rthread) == -1)
  {
    mdprintf(2, "Error : Could not detach receive thread\n");
    return (-1);
  }
  return (0);
}
