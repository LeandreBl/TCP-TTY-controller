/*
** create_sprite.c for create_sprite in /home/leandre/Rushs/scroller
** 
** Made by Léandre Blanchard
** Login   <leandre.blanchard@epitech.eu>
** 
** Started on  Sun Apr  2 12:20:16 2017 Léandre Blanchard
** Last update Sat Oct 14 21:42:49 2017 Léandre Blanchard
*/

#include "csfml.h"
#include "../my.h"
#include "../colors.h"

/*
** add the t_sprite "sprite" on the t_window "window" at the pos.x, pos.y
** will need a call to window_refresh(window) to display it
*/
void			put_sprite(t_window *window, t_sprite *sprite, sfVector2f pos)
{
  sfSprite_setPosition(sprite->sprite, pos);
  sfSprite_setScale(sprite->sprite, xy_vectorf(1, 1));
  sfRenderWindow_drawSprite(window->window, sprite->sprite, NULL);
}
/*
** same as above, but can be resized, for example, resize = { 2, 2 }
** will display the sprite as 2 as large as normal
** does not have any conflict with fonction above
*/
void			put_sprite_resize(t_window *window,
				t_sprite *sprite, sfVector2f pos, sfVector2f resize)
{
  sfSprite_setScale(sprite->sprite, resize);
  sfSprite_setPosition(sprite->sprite, pos);
  sfRenderWindow_drawSprite(window->window, sprite->sprite, NULL);
}
/* 
** primary t_sprite fonction, create a t_sprite from a file
** getting texture in t_sprite->texture and sprite in t_sprite->sprite
** return NULL on ERROR, and t_sprite malloced on SUCCESS
*/
t_sprite		*create_sprite(const char *pathname)
{
  t_sprite		*sprite;

  if ((sprite = malloc(sizeof(t_sprite))) == NULL)
    return (NULL);
  new_printf(BOLDRED);
  if ((sprite->texture = sfTexture_createFromFile(pathname, NULL)) == NULL)
    {
      sfree(&sprite);
      return (NULL);
    }
  new_printf(RESET);
  if ((sprite->sprite = sfSprite_create()) == NULL)
    {
      sfTexture_destroy(sprite->texture);
      sfree(&sprite);
      return (NULL);
    }
  sfSprite_setTexture(sprite->sprite, sprite->texture, sfTrue);
  return (sprite);
}
/*
** create an array of t_sprite, ended by a NULL ptr
** then a call to cerate_sprite must be usefull to fill it
*/
t_sprite        **create_sprites(int nb)
{
  int           i;
  t_sprite      **sprites;

  i = 0;
  if ((sprites = malloc(sizeof(t_sprite *) * (nb + 1))) == NULL)
    return (NULL);
  while (i < nb)
    if ((sprites[i++] = malloc(sizeof(t_sprite))) == NULL)
      return (NULL);
  sprites[nb] = NULL;
  return (sprites);
}
