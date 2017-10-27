/*
** EPITECH PROJECT, 2017
** remote-tty
** File description:
** session end 
*/

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#include "my.h"
#include "defines.h"
#include "colors.h"

#include "remote-tty.h"

int		end_session(session_info_t *session, struct termios *old)
{
  mprintf("\n%sEnding session of : %s\n", RESET, session->username);
  if (tcsetattr(0, TCSANOW, old) == -1)
    mdprintf(2, "Error : Could not reset term configs\n");
  sfree(&session->username);
  sfree(&session->ip);
  if ((session->socket > 0 && close(session->socket) == -1) ||
      (session->csocket > 0 && close(session->csocket) == -1))
  {
    mdprintf(2, "Error : Could not close socket\n");
    return (-1);
  }
  mprintf("Waiting for threads to end : ");
  kill(getpid(), SIGUSR1);
  unlink(RETURN_FILE);
  sleep(1);
  if (session->socket > 0 || session->csocket > 0)
    if (pthread_cancel(session->thread) == -1 ||
	pthread_join(session->thread, NULL) == -1)
    {
      mdprintf(2, "Error : Could not cancel or stop the server thread\n");
      return (-1);
    }
  mprintf("Done\n");
  return (0);
}
