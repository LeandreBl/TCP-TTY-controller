/*
** EPITECH PROJECT, 2017
** catalloc
** File description:
** ptr_functions
*/

#include "my.h"
#include "catalloc.h"

static void		add_fction(char action, ptr_fction_t *index,
				   void *(*fction)(char *src, va_list *va))
{
  index->action = action;
  index->fction = fction;
}

static void		tab_create(ptr_fction_t *tab)
{
  add_fction('c', &tab[0], (void *)add_char);
  add_fction('s', &tab[1], (void *)add_str);
  add_fction('d', &tab[2], (void *)add_number);
  add_fction('f', &tab[3], (void *)add_float);
  add_fction('F', &tab[4], (void *)cata_free);
  add_fction('S', &tab[5], (void *)add_str_free);
}

char			*va_catalloc(const char *format, va_list *va)
{
  static ptr_fction_t	fctions[NB_FCTION];
  static int		called = 0;
  char			*str;

  if (called == 0)
    tab_create(fctions);
  called++;
  str = catalloc_gesture(format, va, fctions);
  return (str);
}
