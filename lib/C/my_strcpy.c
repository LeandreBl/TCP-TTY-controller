/*
** my_strcpy.c for my_strcpy in /home/lblanchard/lbl-libc/C
** 
** Made by Leandre Blanchard
** Login   <lblanchard@epitech.net>
** 
** Started on  Tue Nov  8 19:58:41 2016 Leandre Blanchard
** Last update Thu Oct 12 16:46:39 2017 Leandre Blanchard
*/

#include <unistd.h>

int	my_strcpy(char *dest, const char *src)
{
  int	i;

  if (dest == NULL || src == NULL)
    return (-1);
  i = 0;
  while (*(src + i))
    {
      *(dest + i) = *(src + i);
      ++i;
    }
  *(dest + i) = *(src + i);
  return (0);
}
