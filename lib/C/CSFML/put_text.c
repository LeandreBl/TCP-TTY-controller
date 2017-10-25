/*
** put_text.c for  in /home/leandre/Rushs/scroller/lib/CSFML
** 
** Made by Léandre Blanchard
** Login   <leandre.blanchard@epitech.eu>
** 
** Started on  Fri Mar 31 14:08:05 2017 Léandre Blanchard
** Last update Sat Oct 14 21:44:11 2017 Léandre Blanchard
*/

#include "csfml.h"
#include "../my.h"

/*
** This function allows you to write text on your screen
** using t_window, it will get the font of t_window->font
** and display the word "word" at coordinates "pos"
** with color "color"
** This function does not return
*/
void            put_word(char *word, sfVector2f pos,
			 t_window *window, sfColor color)
{
  sfFont        *font;
  sfText        *text;

  if (window->font != NULL && word != NULL)
    {
      font = sfFont_createFromFile(window->font);
      text = sfText_create();
      sfText_setString(text, word);
      sfText_setFont(text, font);
      sfText_setColor(text, color);
      sfText_setCharacterSize(text, 30);
      sfText_setPosition(text, pos);
      sfRenderWindow_drawText(window->window, text, NULL);
      sfText_destroy(text);
      sfFont_destroy(font);
    }
}
/*
** Same as above but to print a number, 
** first convert it into a char *
** then printing it on the screen
*/
void            put_number(int nb, sfVector2f pos,
			   t_window *window, sfColor color)
{
  char          *str;

  if (nb != 0)
    {
      str = int_char(nb);
      put_word(str, pos, window, color);
      sfree(&str);
    }
  else
    put_word("0", pos, window, sfRed);
}
