/*
** my_strcat.c for my_strcat in /home/lblanchard/CPool_Day07
** 
** Made by Leandre Blanchard
** Login   <lblanchard@epitech.net>
** 
** Started on  Tue Oct 11 09:27:45 2016 Leandre Blanchard
** Last update Wed Oct 25 21:15:41 2017 Léandre Blanchard
*/

#include "my.h"

int	my_strcat(char *dest, const char *src)
{
  if (dest == NULL || src == NULL)
    return (-1);
  while (*dest)
    dest++;
  while ((*dest = *src))
    {
      dest++;
      src++;
    }
  return (0);
}

char	*my_strncat(char *dest, const char *src, int nb)
{
  int	i;

  i = 0;
  while (src[i] != '\0' && nb > 0)
  {
    dest[my_strlen(dest) + i] = src[i];
    i = i + 1;
    nb = nb - 1;
  }
  dest[my_strlen(dest) + 1] = '\0';
  return dest;
}
