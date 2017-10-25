/*
** va_put_tab.c for mprintf in /home/leandre
** 
** Made by Léandre Blanchard
** Login   <leandre.blanchard@epitech.eu>
** 
** Started on  Fri Sep  8 09:33:16 2017 Léandre Blanchard
** Last update Fri Sep  8 09:34:51 2017 Léandre Blanchard
*/

#include "new_printf.h"
#include "my.h"

void		va_put_tab(int fd, va_list *va)
{
  int		i;
  char		**tab;

  tab = va_arg(*va, char **);
  i = 0;
  if (tab == NULL)
    return;
  while (tab[i] != NULL)
    {
      fd_putstr(fd, tab[i]);
      fd_putchar(fd, '\n');
      ++i;
    }
}
