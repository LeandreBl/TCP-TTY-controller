/*
** fd_put.c for va_printf in /home/leandre/Documents/new_printf
** 
** Made by Léandre Blanchard
** Login   <leandre.blanchard@epitech.eu>
** 
** Started on  Thu Sep  7 14:05:47 2017 Léandre Blanchard
** Last update Thu Sep  7 15:53:35 2017 Léandre Blanchard
*/

#include "my.h"
#include "new_printf.h"

void		va_putchar(int fd, va_list *va)
{
  int		c;

  c = va_arg(*va, int);
  fd_putchar(fd, c);
}

void		va_putstr(int fd, va_list *va)
{
  char		*str;

  str = va_arg(*va, char *);
  fd_putstr(fd, str);
}

void		va_putnbr(int fd, va_list *va)
{
  int		nb;

  nb = va_arg(*va, int);
  fd_putnbr(fd, nb);
}

void		va_pointer(int fd, va_list *va)
{
  void		*addr;

  addr = va_arg(*va, void *);
  fd_pointer(fd, addr);
}

void		va_putfloat(int fd, va_list *va)
{
  double       	nbr;

  nbr = va_arg(*va, double);
  fd_putfloat(fd, nbr);
}
