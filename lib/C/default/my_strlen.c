/*
** my_strlen.c for my_strlen in /home/lblanchard/CPool_Day04
** 
** Made by Leandre Blanchard
** Login   <lblanchard@epitech.net>
** 
** Started on  Thu Oct  6 19:01:09 2016 Leandre Blanchard
** Last update Wed Oct  4 22:28:50 2017 Léandre Blanchard
*/

#include <stdlib.h>

int	my_strlen(const char *str)
{
  int	i;

  i = 0;
  if (str == NULL)
    return (0);
  while (str[i] != 0)
    i++;
  return (i);
}

int	my_kstrlen(const char *str, char k)
{
  int	i;

  i = 0;
  if (str == NULL)
    return (0);
  while (str[i] != k && str[i])
    ++i;
  return (i);
}
