/*
** EPITECH PROJECT, 2017
** remote-tty
** File description:
** change color cmd
*/

#include "remote-tty.h"

#include "my.h"
#include "defines.h"
#include "colors.h"

static int	howto(const char *cmd)
{
  if (my_strncmp(cmd, "set color ", 10) != 0)
  {
    mprintf("Usage : !set color <color>\n");
    mprintf("\tcyan\n\tred\n\tgreen\n\tyellow\n\tblue\n\twhite\n");
    prompt();
    return (1);
  }
  return (0);
}

int		set_color(const char *cmd, session_info_t *session)
{
  if (howto(cmd))
    return (0);
  cmd += 10;
  if (my_strcmp(cmd, "cyan") == 0)
    session->color = BOLDCYAN;
  else if (my_strcmp(cmd, "red") == 0)
    session->color = BOLDRED;
  else if (my_strcmp(cmd, "green") == 0)
    session->color = BOLDGREEN;
  else if (my_strcmp(cmd, "yellow") == 0)
    session->color = BOLDYELLOW;
  else if (my_strcmp(cmd, "white") == 0)
    session->color = BOLDWHITE;
  else if (my_strcmp(cmd, "blue") == 0)
    session->color = BOLDBLUE;
  else if (my_strcmp(cmd, "reset") == 0)
    session->color = NULL;
  else
  {
    mdprintf(2, "\"%s\" color is not handled\n", cmd);
    return (0);
  }
  mprintf("Color set to %s\n", cmd);
  return (0);
}
