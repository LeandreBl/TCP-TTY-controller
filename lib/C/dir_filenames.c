/*
** dir_filenames.c for dir_filenames in /home/leandre/TEST_FOLDER
** 
** Made by Léandre Blanchard
** Login   <leandre.blanchard@epitech.eu>
** 
** Started on  Sat Sep 16 15:39:05 2017 Léandre Blanchard
** Last update Sat Oct 14 21:56:12 2017 Léandre Blanchard
*/

#include <sys/types.h>
#include <dirent.h>

#include "my.h"
#include "defines.h"

char		**dir_filenames(const char *dirname, int sort)
{
  char		**filenames;
  DIR		*directory;
  struct dirent	*dirent;

  filenames = NULL;
  if ((directory = opendir(dirname)) == NULL)
    return (NULL);
  while ((dirent = readdir(directory)) != NULL)
    if (dirent->d_type == DT_REG)
      if ((filenames = tab_append(filenames, my_strdup(dirent->d_name))) == NULL)
	return (NULL);
  if (closedir(directory))
    mprintf("%DError : directory <%s> not closed\n", 2, dirname);
  if (sort)
    sort_tab(filenames);
  return (filenames);
}
