//
// Window.cpp for window in /home/leandre/libmy/C++/SFML
// 
// Made by Léandre Blanchard
// Login   <leandre.blanchard@epitech.eu>
// 
// Started on  Mon Jul 24 21:51:44 2017 Léandre Blanchard
// Last update Sun Oct  1 23:56:08 2017 Léandre Blanchard
//

#include "my_sfml.hpp"

Window::~Window(void)
{
  delete[]pixels;
}

void			Window::putWord(std::string word, sf::Vector2f pos, sf::Color color, int size)
{
  sf::Text		text;

  text.setFont(font);
  text.setString(word);
  text.setCharacterSize(size);
  text.setColor(color);
  text.setPosition(pos);
  text.setStyle(sf::Text::Bold);
  win.draw(text);
}

int                     Window::putPixel(sf::Vector2f pos, sf::Color color)
{
  if (pos.x < 0 || pos.y < 0)
    return (-1);
  if (pos.x > win.getSize().x || pos.y >= win.getSize().y)
    return (-1);
  pixels[(win.getSize().x * (int)pos.y + (int)pos.x) * 4 + 0] = color.r;
  pixels[(win.getSize().x * (int)pos.y + (int)pos.x) * 4 + 1] = color.g;
  pixels[(win.getSize().x * (int)pos.y + (int)pos.x) * 4 + 2] = color.b;
  pixels[(win.getSize().x * (int)pos.y + (int)pos.x) * 4 + 3] = color.a;
}

int                     Window::putSquare(sf::Vector2i pos, sf::Color color, int size)
{
  int           i = 0;
  int           j = 0;

  while (i < size)
    {
      putPixel(sf::Vector2f(pos.x + i, pos.y + j), color);
      ++j;
      if (j == size)
	{
	  ++i;
	  j = 0;
	}
    }
}

sf::Vector2i            Window::getMouse(void)
{
  mouse = sf::Mouse::getPosition(win);
  return (mouse);
}

void                    Window::drawLine(sf::Vector2f from, sf::Vector2f to, sf::Color color)
{
  sf::Vector2f          xy;
  double                a;
  double                b;
  sf::Vector2f          swap;

  if (from.x > to.x)
    {
      swap = from;
      from = to;
      to = from;
    }
  a = (to.y - from.y) / (to.x - from.x);
  b = from.y - (a * from.x);
  xy.x = from.x;
  while (xy.x < to.x)
    {
      xy.y = a * xy.x + b;
      putPixel(sf::Vector2f((int)xy.x, (int)xy.y), color);
      xy.x += 0.2;
    }
  while (xy.x < to.x && to.y == from.y)
    putPixel(sf::Vector2f((int)xy.x, (int)xy.y++), color);
}

int			Window::inRect(sf::Vector2f origin, sf::Vector2f size)
{
  getMouse();
  if (mouse.x >= origin.x && mouse.x <= (origin.x + size.x)
      && mouse.y >= origin.y && mouse.y <= (origin.y + size.y))
    return (1);
  return (0);
}

void                    Window::create(int width, int height, std::string title,
				       std::string font_name, sf::Uint32 style)
{
  texture.create(width, height);
  win.RenderWindow::create(sf::VideoMode(width, height), title, style);
  pixel_buffer(width, height);
  font.loadFromFile(font_name);
  focus = true;
}

void                    Window::pixel_buffer(int width, int height)
{
  int			i = 0;

  if ((pixels = new sf::Uint8[win.getSize().x * win.getSize().y * 4]) == NULL)
    std::cerr << "Not enough memory !\n";
  while (i < win.getSize().x * win.getSize().y * 4)
    pixels[i++] = 0;
}

sf::Vector2u            Window::getSize(void)
{
  return (win.getSize());
}

void                    Window::setPixels_color(sf::Color color)
{
  int                   i = 0;
  int                   j = 0;
  int                   size = win.getSize().y;

  while (i < size)
    {
      putPixel(sf::Vector2f(j, i), color);
      ++j;
      if (j == win.getSize().x)
	{
	  j = 0;
	  ++i;
	}
    }
}

void                    Window::refreshPixels(void)
{
  texture.update(pixels);
  sprite.setTexture(texture);
  win.draw(sprite);
  win.display();
}

void                    Window::refresh(void)
{
  win.display();
}

void                    Window::clear(void)
{
  win.clear();
}

void                    Window::clear(sf::Color color)
{
  win.clear(color);
}

void                    Window::draw(sf::Sprite &sprite)
{
  win.draw(sprite);
}

void                    Window::draw(t_sprite &sprite)
{
  win.draw(sprite.sprite);
}

void                    Window::draw(t_sprite &sprite, sf::Vector2f pos)
{
  sprite.setPosition(pos);
  win.draw(sprite.sprite);
}

void                    Window::close(void)
{
  win.close();
}

void			Window::freePixels(void)
{
  delete pixels;
}

int                     Window::isOpen(void)
{
  return (win.isOpen());
}

int			Window::isClose(void)
{
  if (event.type == sf::Event::Closed)
    return (1);
  if (event.type == sf::Event::LostFocus)
    focus = false;
  if (event.type == sf::Event::GainedFocus)
    focus = true;
  return (0);
}

bool			Window::isFocused(void)
{
  return (focus);
}

int                     keyReleased(sf::Keyboard::Key key)
{
  if (KP(key))
    {
      while (KP(key));
      return (1);
    }
  return (0);
}
