//
// key_released.cpp for sfml in /home/leandre/C++/sfml
// 
// Made by Léandre Blanchard
// Login   <leandre.blanchard@epitech.eu>
// 
// Started on  Tue Jul 25 01:36:55 2017 Léandre Blanchard
// Last update Tue Jul 25 01:37:51 2017 Léandre Blanchard
//

#include "my_sfml.hpp"

int			keyReleased(sf::Keyboard::Key key)
{
  if (KP(key))
    {
      while (KP(key));
      return (1);
    }
  return (0);
}
