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
    return (1);
  }
  return (0);
}

int		set_color(const char *cmd, session_info_t *session)
{
  char		*prompt_cur;

  prompt_cur = session->prompt + my_strlen(session->color);
  shift_right(prompt_cur, my_strlen(RESET));
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
  session->prompt = catalloc("%s%s%s%F", session->color, prompt_cur,
			     RESET, session->prompt);
  if (session->prompt == NULL)
    return (-1);
  return (0);
}
