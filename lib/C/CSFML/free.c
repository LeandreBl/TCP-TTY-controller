/*
** free.c for my_csfml in /home/leandre/C_graphical_prog/tekadventure
** 
** Made by Léandre Blanchard
** Login   <leandre.blanchard@epitech.eu>
** 
** Started on  Wed Apr  5 14:48:58 2017 Léandre Blanchard
** Last update Sat Oct 14 21:43:57 2017 Léandre Blanchard
*/

#include "csfml.h"
#include "../my.h"

/*
** When you are loading 5 sprites but with 1 image, such as
** different movement of a player, but cut into pieces,
** so you just loaded 1 texture for the wholes sprites
** which you cut into pieces after, well this fonction
** only frees the texture, and then all the sprites
** replace the freed pointers by NULL
*/
void		free_sprites_only(t_sprite **sprites)
{
  int		i;

  i = 0;
  if (sprites != NULL)
    {
      sfTexture_destroy(sprites[0]->texture);
      while (sprites[i] != NULL)
	{
	  if (sprites[i]->sprite != NULL)
	    sfSprite_destroy(sprites[i]->sprite);
	  sfree(&sprites[i++]);
	}
      sfree(&sprites);
    }
}
/*
** Entirely free a t_sprite ** using a call to free_sprite
** and replace the ptr freed, by NULL
*/
void		free_sprites(t_sprite **sprites)
{
  int		i;

  i = 0;
  if (sprites != NULL)
    {
      while (sprites[i] != NULL)
	{
	  free_sprite(sprites[i]);
	  i++;
	}
      sfree(&sprites);
    }
}
/*
** Frees all sfMusics contained in a sfMusics **
** replaces freed pointers by NULL
*/
void		free_musics(sfMusic **musics)
{
  int		i;

  i = 0;
  if (musics != NULL)
    {
      while (musics[i] != NULL)
	{
	  sfMusic_destroy(musics[i]);
	  i++;
	}
      sfree(&musics);
    }
}
/*
** Free a single t_sprite, then replace it by NULL
*/
void            free_sprite(t_sprite *sprite)
{
  if (sprite != NULL)
    {
      if (sprite->sprite != NULL)
	sfSprite_destroy(sprite->sprite);
      if (sprite->texture != NULL)
	sfTexture_destroy(sprite->texture);
      sfree(&sprite);
    }
}
/*
** Using a lot of calls to above fonctions,
** frees the whole t_window structure
*/
void            free_window(t_window *window)
{
  if (window != NULL)
    {
      if (window->window != NULL)
	sfRenderWindow_destroy(window->window);
      if (window->pixels != NULL)
	sfree(&window->pixels);
      if (window->font != NULL)
	sfree(&window->font);
      free_musics(window->musics);
      if (window->texture != NULL)
	sfTexture_destroy(window->texture);
      if (window->sprite != NULL)
	sfSprite_destroy(window->sprite);
      sfree(&window);
    }
}
