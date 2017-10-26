/*
** EPITECH PROJECT, 2017
** remote-tty
** File description:
** client thread
*/

#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "remote-tty.h"

#include "my.h"
#include "defines.h"

static void		send_thread(session_info_t *session)
{
  while (session->status == STATUS_OK)
  {
    if (session->csocket == -1 && session->side == CLIENT)
      if (connect_client(session) == -1)
      {
	mdprintf(2, "Re-try connection in %d sec ...\n", CON_TIMEOUT);
	sleep(CON_TIMEOUT);
      }
  }
}

int			start_client_thread(session_info_t *session)
{
  if (pthread_create(&session->sthread, NULL,
		     (void *)send_thread, (void *)session) == -1)
  {
    mdprintf(2, "Error : Could not start send thread\n");
    return (-1);
  }
  if (pthread_detach(session->sthread) == -1)
  {
    mdprintf(2, "Error : Could not detach send thread\n");
    return (-1);
  }
  return (0);
}
