/*
** va_put_binary.c for mprintf in /home/lblanchard/lbl-libc/C
** 
** Made by Leandre Blanchard
** Login   <leandre.blanchard@epitech.eu>
** 
** Started on  Thu Oct 12 16:49:48 2017 Leandre Blanchard
** Last update Sat Oct 14 21:31:23 2017 Léandre Blanchard
*/

#include "my.h"
#include "new_printf.h"

# define HEXA "0123456789abcdef"

static void	put_binary(int fd, int bytes)
{
  if (bytes >> 1 != 0)
    put_binary(fd, bytes >> 1);
  fd_putchar(fd, 48 + (1 & bytes));
}

void		va_put_binary(int fd, va_list *va)
{
  int		bytes;

  bytes = va_arg(*va, int);
  if (bytes < 0)
    {
      bytes = -bytes;
      fd_putchar(fd, '-');
    }
  fd_putstr(fd, "0b");
  put_binary(fd, bytes);
}

static void	put_hex(int fd, int nb)
{
  int		res;
  int		rest;

  res = nb / 16;
  rest = nb % 16;
  if (res > 0)
    put_hex(fd, res);
  fd_putchar(fd, HEXA[rest]);
}

void		va_put_hex(int fd, va_list *va)
{
  int		nb;

  nb = va_arg(*va, int);
  if (nb < 0)
  {
    nb = -nb;
    fd_putchar(fd, '-');
  }
  fd_putstr(fd, "0x");
  put_hex(fd, nb);
}
