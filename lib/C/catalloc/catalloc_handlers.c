/*
** EPITECH PROJECT, 2017
** catalloc
** File description:
** functions handled
*/

#include <stdarg.h>
#include <stdlib.h>

#include "my.h"

char				*add_char(char *src, va_list *va)
{
  char				c;

  c = (char)va_arg(*va, int);
  src = insert(src, "x", my_strlen(src));
  if (src == NULL)
    return (NULL);
  src[my_strlen(src) - 1] = c;
  return (src);
}

char				*cata_free(char *src, va_list *va)
{
  void				*to_free;

  to_free = va_arg(*va, void *);
  sfree(&to_free);
  return (src);
}

char				*add_str(char *src, va_list *va)
{
  char				*str;

  str = va_arg(*va, char *);
  if (str == NULL)
    return (src);
  return (insert(src, str, my_strlen(src)));
}

char				*add_str_free(char *src, va_list *va)
{
  char				*str;

  str = va_arg(*va, char *);
  src = insert(src, str, my_strlen(src));
  sfree(&str);
  return (src);
}
