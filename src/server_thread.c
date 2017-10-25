/*
** EPITECH PROJECT, 2017
** remote-tty
** File description:
** server thread
*/

#include <pthread.h>

#include "remote-tty.h"

#include "my.h"
#include "defines.h"

static void		server_thread(session_info_t *session)
{
  mprintf("Je suis le thread de %s\n", session->username);
}

int			start_server_thread(session_info_t *session)
{
  if (pthread_create(&session->thread, NULL,
		     (void *)server_thread, (void *)session) == -1)
  {
    mdprintf(2, "Error : Could not start server thread\n");
    return (-1);
  }
  if (pthread_detach(session->thread) == -1)
  {
    mdprintf(2, "Error : Could not detach server thread\n");
    return (-1);
  }
  return (0);
}
