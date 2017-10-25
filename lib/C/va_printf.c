/*
** va_printf.c for va_printf in /home/leandre/Documents/new_printf
** 
** Made by Léandre Blanchard
** Login   <leandre.blanchard@epitech.eu>
** 
** Started on  Thu Sep  7 12:39:57 2017 Léandre Blanchard
** Last update Thu Oct 12 17:20:12 2017 Leandre Blanchard
*/

#include <stdlib.h>

#include "my.h"
#include "new_printf.h"

void			va_fputstr(int fd, va_list *va)
{
  char			*str;

  str = va_arg(*va, char *);
  fd_putstr(fd, str);
  sfree(&str);
}

static t_fctptr		add_fction(char action,
				   void *(*fction)(int fd, va_list *va))
{
  t_fctptr		tab;

  tab.action = action;
  tab.fction = fction;
  return (tab);
}

static void		tab_create(t_fctptr *tab)
{
  tab[0] = add_fction('s', (void *)va_putstr);
  tab[1] = add_fction('c', (void *)va_putchar);
  tab[2] = add_fction('d', (void *)va_putnbr);
  tab[3] = add_fction('p', (void *)va_pointer);
  tab[4] = add_fction('f', (void *)va_putfloat);
  tab[5] = add_fction('F', (void *)va_free);
  tab[6] = add_fction('S', (void *)va_fputstr);
  tab[7] = add_fction('k', (void *)va_cutstr);
  tab[8] = add_fction('T', (void *)va_put_tab);
  tab[9] = add_fction('b', (void *)va_put_binary);
  tab[10] = add_fction('x', (void *)va_put_hex);
  tab[NB_FCT] = add_fction(0, NULL);
}

int			va_printf(int fd, const char *format, va_list *va)
{
  static t_fctptr	fctions[NB_FCT + 1];
  static int		called = 0;

  if (called == 0)
    tab_create(fctions);
  called++;
  format_gesture(fd, va, fctions, format);
  return (0);
}
