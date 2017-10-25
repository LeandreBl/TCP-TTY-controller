/*
** in_rect.c for CSFML in /home/leandre/C_graphical_prog/tekadventure
** 
** Made by Léandre Blanchard
** Login   <leandre.blanchard@epitech.eu>
** 
** Started on  Thu Apr 20 09:14:16 2017 Léandre Blanchard
** Last update Sat Jun  3 16:47:45 2017 Léandre Blanchard
*/

#include "csfml.h"

/*
** This function refresh the position of the mouse in t_window->mouse
** and return 0 if the mouse is located in the rectangle 
** of size size.x * size.y who upper-left corner is at (origin.x, origin.y)
*/
int		is_in_rect(t_window *window, sfVector2f origin, sfVector2f size)
{
  pos_mouse(window);
  if (window->mouse.x >= origin.x && window->mouse.x <= (origin.x + size.x)
      && window->mouse.y >= origin.y && window->mouse.y <= (origin.y + size.y))
    return (0);
  return (1);
}
