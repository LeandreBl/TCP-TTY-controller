/*
** my_strdup.c for my_strdup in /home/lblanchard/CPool_Day08
** 
** Made by Leandre Blanchard
** Login   <lblanchard@epitech.net>
** 
** Started on  Wed Oct 12 09:15:56 2016 Leandre Blanchard
** Last update Thu Oct 12 18:18:54 2017 Leandre Blanchard
*/

#include <unistd.h>

#include "my.h"

char	*my_strdup(const char *src)
{
  char	*dest;

  if (src == NULL)
    return (NULL);
  if ((dest = my_calloc(sizeof(char) * (my_strlen(src) + 1))) == NULL)
    return (NULL);
  my_strcpy(dest, src);
  return (dest);
}
