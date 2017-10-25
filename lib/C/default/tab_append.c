/*
** tab_append.c for tab_append in /home/leandre
** 
** Made by Léandre Blanchard
** Login   <leandre.blanchard@epitech.eu>
** 
** Started on  Sun May 14 20:03:11 2017 Léandre Blanchard
** Last update Wed Oct 25 21:19:52 2017 Léandre Blanchard
*/

#include <stdlib.h>

#include "my.h"

char		**tab_append(char **tab, char *add)
{
  char		**new;
  int		i;

  i = 0;
  if ((new = malloc(sizeof(char *) * (tablen(tab) + 2))) == NULL)
    return (NULL);
  while (tab != NULL && tab[i] != NULL)
    {
      new[i] = tab[i];
      ++i;
    }
  new[i] = add;
  new[i + 1] = NULL;
  if (tab != NULL)
    sfree(&tab);
  return (new);
}
