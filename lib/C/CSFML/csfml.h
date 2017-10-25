/*
** csfml.h for csfml_h_lib in /home/leandre/Rushs/scroller/lib/CSFML
** 
** Made by Léandre Blanchard
** Login   <leandre.blanchard@epitech.eu>
** 
** Started on  Fri Mar 31 13:58:23 2017 Léandre Blanchard
** Last update Sat Oct 14 22:02:11 2017 Léandre Blanchard
*/

#ifndef MY_CSFML_H_
# define MY_CSFML_H_

#ifdef __cplusplus
extern "C" {
#endif

# include <SFML/Audio.h>
# include <SFML/Network.h>
# include <SFML/Graphics.h>
# include <SFML/System.h>
# include <SFML/Window.h>

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stddef.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <time.h>
# include <termios.h>
# include <curses.h>
# include <dirent.h>

# include "my.h"

# define KP(key) sfKeyboard_isKeyPressed(key)
# define MP sfMouse_isButtonPressed(sfMouseLeft)
/*
** A window structure, containing it's size,
** the position of the mouse using pos_mouse
** a char * containing the name of the font for
** put_text fcontions
** an array of pixels, of the size of the window
** an array of sfMusics *ptr
** a texture linked to the array of pixels, same for the sprite
*/
typedef struct		s_window
{
  int			width;
  int			height;
  sfVector2i		mouse;
  sfRenderWindow	*window;
  sfUint8		*pixels;
  char			*font;
  sfMusic		**musics;
  sfTexture		*texture;
  sfSprite		*sprite;
}			t_window;
/*
** Simple sprite structure, saving the texture and the sprite,
** can be easely used with put_sprite, and create via a call
** of create_sprite(<pathname>)
*/
typedef struct		s_sprite
{
  sfSprite		*sprite;
  sfTexture		*texture;
}			t_sprite;

typedef t_window t_win;

void		my_draw_line(t_window *window, sfVector2f from,
			     sfVector2f to, sfColor color);

void		free_sprite(t_sprite *sprite);

void		free_sprites_only(t_sprite **sprites);

sfUint8		*pixels_buffer(int width, int height);

void		free_thread(sfThread *thread);

void		free_window(t_window *window);

void		free_sprites(t_sprite **sprites);

t_sprite	**create_sprites(int nb);

int		is_in_rect(t_window *window, sfVector2f origin, sfVector2f size);

void		window_clear(t_window *window);

int		key_released(int key);

void		window_refresh(t_window *window);

void		put_sprite(t_window *window, t_sprite *sprite, sfVector2f pos);

void		put_sprite_resize(t_window *window, t_sprite *sprite,
				  sfVector2f pos, sfVector2f resize);

void		close_win(t_window *window);

sfVector2i	xy_vectori(int x, int y);

sfVector2f      xy_vectorf(float x, float y);

sfVector3f      xyz_vector(float x, float y, float z);

sfVector2i	pos_mouse(t_window *window);

void		put_square(sfVector2i pos, sfColor color,
			   t_window *window, int size);

void		draw_circle(t_window *window, sfVector2f pos,
			    int size, sfColor color);

void            put_png_resize(t_window *window, sfVector2f pos,
			       const char *name, sfVector2f resize);

void            put_png(t_window *window, sfVector2f pos, const char *name);

int             my_put_pixel(t_window *window, int x, int y, sfColor color);

void		clear_white(t_window *window);

void		put_word(char *word, sfVector2f pos,
			 t_window *window, sfColor color);

void            put_number(int nb, sfVector2f pos,
			   t_window *window, sfColor color);

t_window	*init_window(int height, float dim, char *name, int bar);

t_sprite	*create_sprite(const char *pathname);

#ifdef __cplusplus
}
#endif

#endif /* !MY_CSFML_H_ */
