/*
** EPITECH PROJECT, 2017
** catalloc
** File description:
** catalloc header
*/

#ifndef CATALLOC_H_
# define CATALLOC_H_

# include <stdarg.h>

struct	ptr_fction_s
{
  char	action;
  void	*(* fction)(char *src, va_list *va);
};

# define NB_FCTION (6)

typedef struct ptr_fction_s ptr_fction_t;

char	*catalloc_gesture(const char *format, va_list *va,
			  ptr_fction_t fctions[]);
char	*va_catalloc(const char *format, va_list *va);
char	*add_char(char *src, va_list *va);
char	*add_number(char *src, va_list *va);
char	*add_str(char *src, va_list *va);
char	*add_str_free(char *src, va_list *va);
char	*add_float(char *src, va_list *va);
char	*cata_free(char *src, va_list *va);

#endif /* !CATALLOC_H_ */
