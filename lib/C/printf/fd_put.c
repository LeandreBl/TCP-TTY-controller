/*
** fd_put.c for printf in /home/leandre/Documents/new_printf
** 
** Made by Léandre Blanchard
** Login   <leandre.blanchard@epitech.eu>
** 
** Started on  Thu Sep  7 14:58:28 2017 Léandre Blanchard
** Last update Wed Oct 25 21:21:29 2017 Léandre Blanchard
*/

#include <stdlib.h>
#include <unistd.h>

#include "my.h"

void		fd_putchar(int fd, int c)
{
  write(fd, &c, 1);
}

void		fd_putstr(int fd, const char *str)
{
  if (str == NULL)
    write(fd, "NULL", 4);
  else
    write(fd, str, my_strlen(str));
}

void		fd_putnbr(int fd, int nbr)
{
  if (nbr < 0)
    {
      fd_putchar(fd, '-');
      nbr = -nbr;
    }
  if (nbr / 10 != 0)
    fd_putnbr(fd, nbr / 10);
  fd_putchar(fd, nbr % 10 + 48);
}

void			fd_pointer(int fd, void *ptr)
{
  char			*base;
  char			*result;
  unsigned long long    i;
  unsigned long long    j;
  unsigned long long    addr;

  addr = (long)ptr;
  j = 0;
  i = addr;
  if ((result = my_calloc(sizeof (char) * 100)) == NULL)
    return;
  if ((base = my_strdup("0123456789abcedf")) == NULL)
    {
      sfree(&result);
      return;
    }
  while (i != 0)
    {
      result[j] = base[i % 16];
      i = i / 16;
      j = j + 1;
    }
  fd_putstr(fd, revstr(result));
  sfree(&result);
  sfree(&base);
}

void			fd_putfloat(int fd, double nbr)
{
  unsigned long long	integer;
  unsigned long long	floating;

  if (nbr < 0)
    {
      my_putchar('-');
      nbr = -nbr;
    }
  integer = (unsigned long long)nbr;
  nbr = (nbr - integer) * 100000000;
  floating = (unsigned long long)nbr;
  while (floating % 10 == 0 && floating != 0)
    floating /= 10;
  fd_putnbr(fd, integer);
  fd_putchar(fd, '.');
  fd_putnbr(fd, floating);
}
