//
// button.cpp for chess in /home/leandre/C++/sfml
// 
// Made by Léandre Blanchard
// Login   <leandre.blanchard@epitech.eu>
// 
// Started on  Wed Jul 26 01:40:33 2017 Léandre Blanchard
// Last update Mon Aug  7 01:40:54 2017 Léandre Blanchard
//

#include "my_sfml.hpp"

void		Button::setScale(sf::Vector2f size)
{
  setScale(size.x, size.y);
}

void		Button::setScale(double x, double y)
{
  sprite.sprite.setScale(x, y);
  if (&onClick != &sprite)
    onClick.sprite.setScale(x, y);
  if (&onRect != &sprite)
    onRect.sprite.setScale(x, y);
}

int		Button::Click(void)
{
  if (MP && inRect() && win->isFocused())
    return (1);
  return (0);
}

int		Button::Release(void)
{
  if (Click() && win->isFocused())
    {
      while (MP);
      if (inRect())
	return (1);
    }
  return (0);
}

sf::Vector2i	Button::getPosition(void)
{
  return (sf::Vector2i(sprite.sprite.getPosition()));
}

void		Button::draw(void)
{
  if (inRect() && win->isFocused())
    {
      if (MP)
	win->draw(onClick);
      else
	win->draw(onRect);
    }
  else
    win->draw(sprite);
}

void		Button::create(std::string image, std::string buttonname, Window *linked_win)
{
  std::string	dup;

  dup = image;
  if (dup.find(".") != std::string::npos)
    {
      while (dup[dup.length() - 1] != '.')
	dup.pop_back();
      dup[dup.length() - 1] = '_';
    }
  sprite.create(image);
  name = buttonname;
  win = linked_win;
  addClickRect(dup + "pressed.png", dup + "in.png");
}

void		Button::addClickRect(std::string click, std::string rect)
{
  if (onClick.create(click) == -1)
    onClick = sprite;
  else
    {
      onClick.setPosition(sf::Vector2f(getPosition()));
      onClick.sprite.setScale(sprite.sprite.getScale());
    }
  if (onRect.create(rect) == -1)
    onRect = sprite;
  else
    {
      onRect.setPosition(sf::Vector2f(getPosition()));
      onRect.sprite.setScale(sprite.sprite.getScale());
    }
}

int		Button::inRect(void)
{
  return (sprite.inRect(*win));
}

void		Button::setPosition(sf::Vector2i pos)
{
  sprite.setPosition(pos.x, pos.y);
  onClick.setPosition(pos.x, pos.y);
  onRect.setPosition(pos.x, pos.y);
}

void		Button::setPosition(sf::Vector2f pos)
{
  sprite.setPosition(pos);
  onClick.setPosition(pos);
  onRect.setPosition(pos);
}

void		Button::setPosition(float x, float y)
{
  sprite.setPosition(x, y);
  onClick.setPosition(x, y);
  onRect.setPosition(x, y);
}

sf::Vector2i	Button::getSize(void)
{
  return (sprite.getSize());
}

void		Button::drawName(int size, sf::Color color)
{
  sf::Text	text;
  sf::Vector2i	pos = getPosition();

  text.setFont(win->font);
  text.setString(name);
  text.setCharacterSize(size);
  text.setColor(color);
  text.setStyle(sf::Text::Bold);
  pos.x += getSize().x / 2 - (name.length() / 2 * size / 2) - size / 3;
  pos.y += getSize().y / 2 - size / 1.6;
  text.setPosition(pos.x, pos.y);
  win->win.draw(text);
}

void		Button::draw(int size, sf::Color color)
{
  draw();
  drawName(size, color);
}
