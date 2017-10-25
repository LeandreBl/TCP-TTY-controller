/*
** va_cutstr.c for mprintf in /home/leandre/TEST_FOLDER
** 
** Made by Léandre Blanchard
** Login   <leandre.blanchard@epitech.eu>
** 
** Started on  Fri Sep  8 09:09:31 2017 Léandre Blanchard
** Last update Thu Oct 12 16:41:33 2017 Leandre Blanchard
*/

#include <unistd.h>

#include "new_printf.h"
#include "my.h"

void			va_cutstr(int fd, va_list *va)
{
  const char		*str;
  const char		*ptr;
  int			jmp;
  int			len;

  str = va_arg(*va, char *);
  jmp = va_arg(*va, int);
  len = my_strlen(str);
  ptr = str;
  while (ptr + jmp < str + len)
    {
      write(fd, ptr, jmp);
      write(fd, " ", 1);
      ptr += jmp;
    }
  if (ptr < str + len)
    fd_putstr(fd, ptr);
}
