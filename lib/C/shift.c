/*
** shift.c for shift in /home/leandre/System_unix/PSU_2016_minishell2
** 
** Made by Léandre Blanchard
** Login   <leandre.blanchard@epitech.eu>
** 
** Started on  Mon Apr  3 18:54:59 2017 Léandre Blanchard
** Last update Tue Sep 12 13:09:29 2017 Léandre Blanchard
*/

#include "my.h"

void		shift_left(char *s, int nb)
{
  int		i;
  int		status;

  status = 0;
  if (s == NULL)
    return;
  while (status != nb)
    {
      i = 0;
      while (s[i] != 0)
	{
	  s[i] = s[i + 1];
	  ++i;
	}
      status++;
    }
}

void		shift_right(char *s, int nb)
{
  if (s == NULL)
    return;
  my_revstr(s);
  shift_left(s, nb);
  my_revstr(s);
}
