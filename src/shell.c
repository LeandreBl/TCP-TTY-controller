/*
** EPITECH PROJECT, 2017
** remote-tty
** File description:
** shell commands from session
*/

#include <stdlib.h>

#include "remote-tty.h"

#include "my.h"
#include "defines.h"

int		i_command(const char *cmd, __attribute__ ((unused)) session_info_t *session)
{
  int		alloc;

  cmd += 2;
  alloc = 0;
  if (my_strncmp(cmd, "ls", 2) == 0 || my_strncmp(cmd, "grep", 4) == 0)
  {
    cmd = catalloc("%s --color=tty", cmd);
    if (cmd == NULL)
      return (-1);
    alloc = 1;
  }
  if (system(cmd) == -1)
  {
    mdprintf(2, "Error : Could not execute %s\n", cmd);
    return (-1);
  }
  if (alloc)
    sfree(&cmd);
  return (0);
}
