/*
** my_strncmp.c for my_strncmp in /home/lblanchard/CPool_Day06
**
** Made by Leandre Blanchard
** Login   <lblanchard@epitech.net>
**
** Started on  Thu Oct  6 11:19:22 2016 Leandre Blanchard
** Last update Sat Oct 14 21:31:14 2017 Léandre Blanchard
*/

#include <stdlib.h>

int	my_strncmp(const char *s1, const char *s2, int n)
{
  if (s1 == NULL || s2 == NULL)
    return (0);
  --n;
  while (*s1 && *s2 && *s1 == *s2 && n)
    {
      ++s1;
      ++s2;
      --n;
    }
  return (*s1 - *s2);
}
