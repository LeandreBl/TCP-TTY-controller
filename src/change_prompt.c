/*
** EPITECH PROJECT, 2017
** remote-tty
** File description:
** change prompt custom
*/

#include "remote-tty.h"

#include "my.h"
#include "defines.h"
#include "colors.h"

int		set_prompt(const char *cmd, session_info_t *session)
{
  if (my_strlen(cmd) <= my_strlen("set prompt "))
    return (-1);
  sfree(&session->prompt);
  cmd += 11;
  session->prompt = catalloc("%s%s%s", session->color, cmd, RESET);
  if (session->prompt == NULL)
    return (-1);
  return (0);
}
