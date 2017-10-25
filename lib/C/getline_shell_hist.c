/*
** EPITECH PROJECT, 2017
** getline_shell
** File description:
** hist
*/

#include "my.h"
#include "defines.h"
#include "getline_shell.h"

void		new_hist(t_curset *curset, int dir)
{
  shift_right(curset->s, 1);
  while (curset->hist >= 0 && curset->hist < my_tablen(curset->cmds)
	 && my_strcmp(curset->s, curset->cmds[curset->hist]) == 0)
    curset->hist += dir;
  if (curset->hist < 0)
    curset->hist = 0;
  if (curset->hist < my_tablen(curset->cmds) && curset->hist >= 0)
  {
    sfree(&curset->s);
    curset->s = my_strdup(curset->cmds[curset->hist]);
  }
  if (curset->hist >= my_tablen(curset->cmds))
  {
    curset->hist = my_tablen(curset->cmds);
    sfree(&curset->s);
    curset->s = my_calloc(2);
  }
  if (curset->hist == my_tablen(curset->cmds))
    zeros(curset->s, my_strlen(curset->s));
}
