//
// my_sfml.cpp for my_sfml in /home/leandre/libmy/C++/SFML
// 
// Made by Léandre Blanchard
// Login   <leandre.blanchard@epitech.eu>
// 
// Started on  Mon Jul 24 21:50:40 2017 Léandre Blanchard
// Last update Mon Aug  7 01:37:46 2017 Léandre Blanchard
//

#include "my_sfml.hpp"

int		t_sprite::hit(sf::Vector2f pos)
{
  if (pos.x >= sprite.getPosition().x && pos.x <= sprite.getPosition().x + getSize().x
      && pos.y >= sprite.getPosition().y && pos.y <= sprite.getPosition().y + getSize().y)
    return (true);
  return (false);
}

int            t_sprite::create(const std::string &filename)
{
  if (!texture.loadFromFile(filename))
    return (-1);
  sprite.setTexture(texture);
}

void            t_sprite::setPosition(float x, float y)
{
  sprite.setPosition(x, y);
}

void            t_sprite::setPosition(sf::Vector2f pos)
{
  sprite.setPosition(pos.x, pos.y);
}

int             t_sprite::inRect(Window &window)
{
  if (window.inRect(sprite.getPosition(),
		    sf::Vector2f(texture.getSize().x * sprite.getScale().x,
				 texture.getSize().y * sprite.getScale().y)))
    return (true);
  return (false);
}

sf::Vector2i	t_sprite::getSize(void)
{
  return (sf::Vector2i(texture.getSize().x * sprite.getScale().x,
		       texture.getSize().y * sprite.getScale().y));
}
