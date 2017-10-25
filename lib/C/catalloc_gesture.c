/*
** EPITECH PROJECT, 2017
** catalloc
** File description:
** catalloc gesture
*/

#include "my.h"
#include "catalloc.h"

static int	loop(va_list *va, ptr_fction_t fctions[],
		     char **cur, char **str)
{
  int		i;

  i = 0;
  while (i < NB_FCTION)
  {
    if (fctions[i].action == *(*cur + 1))
    {
      *str = fctions[i].fction(*str, va);
      *cur += 2;
      return (i);
    }
    ++i;
  }
  return (i);
}

static int	lenframe(const char *str)
{
  int		i;

  i = 0;
  while (str[i] != 0)
  {
    if (str[i] == '%' && str[i + 1] != '%')
      return (i);
    ++i;
  }
  return (i);
}

static int	len_add_str(char **str, char **cur)
{
  int		size;

  size = lenframe(*cur);
  *str = my_frealloc(*str, size + 1);
  if (*str == NULL)
    return (-1);
  my_strncpy(*str + my_strlen(*str), *cur, size);
  *cur += size;
  return (0);
}

char		*catalloc_gesture(const char *format, va_list *va,
				  ptr_fction_t fctions[])
{
  char		*str;
  char		*cur;
  int		len;

  len = my_strlen(format);
  str = my_strdup("");
  cur = (char *)format;
  if (str == NULL)
    return (NULL);
  while (cur < format + len)
  {
    if (len_add_str(&str, &cur) == -1)
      return (NULL);
    if (*cur == '%')
    {
      if (loop(va, fctions, &cur, &str) >= NB_FCTION)
      {
	str = my_frealloc(str, 2);
	my_strncpy(str + my_strlen(str), cur, 2);
	cur += 2;
      }
    }
  }
  return (str);
}
