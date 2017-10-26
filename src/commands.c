/*
** EPITECH PROJECT, 2017
** remote-tty
** File description:
** user cmds
*/

#include "remote-tty.h"

#include "my.h"
#include "colors.h"
#include "defines.h"

static void		add_fction(const char *action,
				   int (*fction)(const char *cmd,
						 session_info_t *session),
				   cmd_ptr_tab_t *index)
{
  index->action = action;
  index->fction = fction;
}

static void		init_tab(cmd_ptr_tab_t tab[])
{
  add_fction("change color", (void *)change_color, &tab[0]);
}

static int		helper(cmd_ptr_tab_t tab[])
{
  int			i;

  i = 0;
  mprintf("Available commands are : \n");
  while (i < NB_CMDS)
  {
    mprintf("\t!%s\n", tab[i].action);
    ++i;
  }
  return (0);
}

int			user_command(const char *cmd, session_info_t *session)
{
  static cmd_ptr_tab_t	tab[NB_CMDS];
  static int		calls;
  int			i;

  i = 0;
  if (calls == 0)
    init_tab(tab);
  calls++;
  if (my_strcmp(cmd, "exit") == 0 || my_strcmp(cmd, "quit") == 0)
    return (1);
  if (my_strcmp(cmd, "help") == 0 || my_strcmp(cmd, "?") == 0)
    return (helper(tab));
  while (i < NB_CMDS)
  {
    if (my_strncmp(tab[i].action, cmd, my_strlen(tab[i].action)) == 0)
      return (tab[i].fction(cmd, session));
    ++i;
  }
  return (0);
}