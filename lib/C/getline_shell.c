/*
** EPITECH PROJECT, 2017
** getline_shell
** File description:
** main functions
*/

#include "my.h"
#include "defines.h"
#include "getline_shell.h"

int                     routine_ioctl(void)
{
  struct termios        new;

  if (ioctl(0, TCGETS, &new) == -1)
    return (-1);
  new.c_lflag &= ~ICANON;
  new.c_lflag &= ~ECHO;
  new.c_cc[VINTR] = 0;
  new.c_cc[VMIN] = 1;
  new.c_cc[VTIME] = 1;
  if (ioctl(0, TCSETS, &new) == -1)
    return (-1);
  return (0);
}

static void		init_tab_ptr(int (*tab_ptr[NB_PTR]) (t_curset *))
{
  tab_ptr[0] = ret_back;
  tab_ptr[1] = ctrl_d;
  tab_ptr[2] = left_key;
  tab_ptr[3] = right_key;
  tab_ptr[4] = up_key;
  tab_ptr[5] = down_key;
  tab_ptr[6] = cur_end;
  tab_ptr[7] = cur_home;
  tab_ptr[8] = ctrl_l;
  tab_ptr[9] = ctrl_c;
  tab_ptr[10] = ctrl_k;
}

static void		init_curset(t_curset *curset, char **cmds,
				    const char *prompt)
{
  curset->prompt = prompt;
  curset->ch = 0;
  curset->cur = 0;
  curset->hist = my_tablen(cmds) - 1;
  curset->cmds = cmds;
  curset->i = 0;
  curset->s = my_calloc(2);
}

static int		add_char(t_curset *curset)
{
  static char		c[3] = "\0\0\0";

  c[0] = c[1];
  c[1] = c[2];
  c[2] = curset->ch;
  if (curset->cur < 0)
    curset->cur = 0;
  if (curset->i == NB_PTR && curset->ch != 3 && curset->ch != 4
                     && curset->ch != 127 && curset->ch != 12
      && curset->ch != 10 && curset->ch != 27 && curset->ch != 11)
    {
      if (c[2] != 91 && c[1] != 27 && curset->ch != '\t')
	move_and_add(curset->s, curset->cur, curset->ch);
      else if (curset->ch != '\t')
	curset->s[my_strlen(curset->s)] = curset->ch;
      curset->cur++;
    }
  if (curset->cur > my_strlen(curset->s))
    curset->cur = my_strlen(curset->s);
  return (0);
}

char			*get_cmd(char **cmds, const char *prompt)
{
  static int		calls;
  static int   		(*tab_ptr[NB_PTR]) (t_curset *);
  t_curset		curset;

  disp_prompt(prompt);
  init_curset(&curset, cmds, prompt);
  if (curset.s == NULL)
    return (NULL);
  if (calls == 0)
  {
    init_tab_ptr(tab_ptr);
    calls = 1;
  }
  while (curset.ch != 10)
    {
      read(0, &curset.ch, 1);
      curset.i = 0;
      if ((curset.s = my_frealloc(curset.s, 2)) == NULL)
	return (NULL);
      while (curset.i < NB_PTR && tab_ptr[curset.i](&curset) != 0)
	curset.i++;
      if (curset.s == NULL)
	return (NULL);
      add_char(&curset);
      if (alt_l(&curset) == 0)
	return (strdup("ls"));
      print_cur(curset.cur, curset.s, prompt);
    }
  mprintf("\n");
  return (curset.s);
}
