/*
** my_strcmp.c for my_strcmp in /home/lblanchard/CPool_Day06
**
** Made by Leandre Blanchard
** Login   <lblanchard@epitech.net>
**
** Started on  Thu Oct  6 11:19:22 2016 Leandre Blanchard
** Last update Fri Oct 13 11:44:45 2017 Leandre Blanchard
*/

#include <stdlib.h>

int	my_strcmp(const char *s1, const char *s2)
{
  if (s1 == NULL || s2 == NULL)
    return (0);
  while (*s1 && *s2 && *s1 == *s2)
    {
      ++s1;
      ++s2;
    }
  if (*s1 - *s2 < 0)
    return (-1);
  if (*s1 - *s2 > 0)
    return (1);
  return (0);
}

