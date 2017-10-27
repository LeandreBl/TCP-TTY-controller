/*
** EPITECH PROJECT, 2017
** remote-tty
** File description:
** the !command command
*/

#include <stdlib.h>

#include "remote-tty.h"

#include "my.h"
#include "colors.h"
#include "defines.h"

static int	accept_error(const char *cmd, session_info_t *session)
{
  if (my_strcmp(cmd, "accept") && session->command != NULL)
  {
    mprintf("\rOnly type !accept or !command accept\n");
    return (-1);
  }
  if (session->command == NULL)
  {
    mprintf("Error : You've received no command at all\n");
    return (0);
  }
  mprintf("Executing : %s%s%s\n", BOLDWHITE, session->command, RESET);
  return (1);
}

int             accept_command(const char *cmd, session_info_t *session)
{
  int		error;

  error = accept_error(cmd, session);
  if (error != 1)
    return (error);
  if (my_strncmp(session->command, "ls", 2) == 0 ||
      my_strncmp(session->command, "grep", 4) == 0)
  {
    session->command = catalloc("%S --color=auto", session->command);
    if (cmd == NULL)
      return (-1);
  }
  session->command = catalloc("%S&", session->command);
  if (session->command == NULL)
    return (-1);
  if (system(session->command) == -1)
  {
    mdprintf(2, "Error : Could not execute %s\n", session->command);
    sfree(&session->command);
    return (0);
  }
  sfree(&session->command);
  return (0);
}

static int	display_session_command(const char *cmd, session_info_t *session)
{
  if (my_strcmp(cmd, "command display"))
    return (-1);
  if (session->command == NULL)
  {
    mprintf("No command found\n");
    return (0);
  }
  mprintf("Last remoted command is : %s%s%s\n", BOLDWHITE, session->command, RESET);
  return (0);
}

static int	clear_session_command(const char *cmd, session_info_t *session)
{
  if (my_strcmp(cmd, "command clear"))
    return (-1);
  if (session->command == NULL)
  {
    mprintf("Command already empty\n");
    return (0);
  }
  mprintf("Command %s%s%s CLEARED\n", BOLDWHITE, session->command, RESET);
  sfree(&session->command);
  return (0);
}

int		display_command(const char *cmd, session_info_t *session)
{
  if (my_strlen(cmd) < my_strlen("command "))
  {
    mprintf("Usage : command \\\n\tdisplay\n\tclear\n\taccept\n");
    return (-1);
  }
  if (display_session_command(cmd, session) == 0)
    return (0);
  if (clear_session_command(cmd, session) == 0)
    return (0);
  if (my_strcmp(cmd, "command accept") == 0 &&
      accept_command("accept", session) == 0)
    return (0);
  return (0);
}
