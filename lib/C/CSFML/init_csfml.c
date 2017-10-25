/*
** init_csfml.c for init_csfml_structs in /home/leandre/Rushs/scroller/lib/CSFML
** 
** Made by Léandre Blanchard
** Login   <leandre.blanchard@epitech.eu>
** 
** Started on  Fri Mar 31 14:24:11 2017 Léandre Blanchard
** Last update Wed Sep  6 16:13:24 2017 Léandre Blanchard
*/

#include "csfml.h"

/*
** Create the sfRenderWindow object, with it's size and name
** return NULL on error
*/
sfRenderWindow          *create_window(char *name, int width,
				       int height, int bar)
{
  sfRenderWindow        *window;
  sfVideoMode           mode;

  if (bar == -1)
    bar = sfClose | sfResize | sfTitlebar;
  mode.width = width;
  mode.height = height;
  mode.bitsPerPixel = 32;
  window = sfRenderWindow_create(mode, name, bar, NULL);
  if (window == NULL)
    return (NULL);
  return (window);
}
/*
** Create a sfUint8 array of pixels, of size width * heiht
** multiplied by 4, for R G B A.
** return NULL on error
*/
sfUint8                 *pixels_buffer(int width, int height)
{
  int                   i;
  sfUint8               *pixels;

  if ((pixels = malloc(4 * width * height)) == NULL)
    return (NULL);
  i = 0;
  while (i != width * height * 4)
    pixels[i++] = 0;
  return (pixels);
}
/*
** Create a t_window object, all malloc and initialized with NULL
** for a Window names "CSFML" of size 1280 * 720
** you'll have to call init_window(720, 16 / 9, "CSFML)
** dim is the ratio of the screen, such as 16/9, 4/3 ...
** bar can be set so the window has no button on top of it, so you can create
** your owns ! by entering 0, other possibility are sfClose | sfResize | sfTitlebar
** return NULL on error
*/
t_window		*init_window(int height, float dim, char *name, int bar)
{
  t_window		*window;

  if ((window = malloc(sizeof(t_window))) == NULL)
    return (NULL);
  window->height = height;
  window->width = window->height * dim;
  window->window = create_window(name,
				 window->width, window->height, bar);
  window->sprite = sfSprite_create();
  window->texture = sfTexture_create(window->width, window->height);
  sfSprite_setTexture(window->sprite, window->texture, sfTrue);
  if ((window->pixels = pixels_buffer(window->width, window->height)) == NULL)
    return (NULL);
  window->font = NULL;
  window->musics = NULL;
  return (window);
}

