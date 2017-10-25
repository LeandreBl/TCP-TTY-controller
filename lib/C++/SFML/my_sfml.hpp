//
// my_sfml.hpp for sfml in /home/leandre/C++/sfml
// 
// Made by Léandre Blanchard
// Login   <leandre.blanchard@epitech.eu>
// 
// Started on  Sun Jul 23 20:34:32 2017 Léandre Blanchard
// Last update Mon Aug  7 01:53:53 2017 Léandre Blanchard
//

#ifndef MY_SFML_HPP_
# define MY_SFML_HPP_

# include <SFML/Audio.hpp>
# include <SFML/Network.hpp>
# include <SFML/Graphics.hpp>
# include <SFML/System.hpp>
# include <SFML/Window.hpp>

# include <iostream>
# include <vector>
# include <fstream>
# include <cstdlib>

# define MP (sf::Mouse::isButtonPressed(sf::Mouse::Left))
# define KP(x) (sf::Keyboard::isKeyPressed(x))

# define PS3_SELECT	0
# define PS3_L3		1
# define PS3_R3		2
# define PS3_START	3
# define PS3_UP		4
# define PS3_RIGHT	5
# define PS3_DOWN	6
# define PS3_LEFT	7
# define PS3_L2		8
# define PS3_R2		9
# define PS3_L1		10
# define PS3_R1		11
# define PS3_TRIANGLE	12
# define PS3_ROND	13
# define PS3_CROIX	14
# define PS3_SQUARE	15
# define PS3_HOME	16

class			t_sprite
{
public :
  sf::Sprite		sprite;
  sf::Texture		texture;

  int			hit(sf::Vector2f pos);
  int			create(const std::string &filename);
  void			link(class Window &window, std::string name);
  void			setPosition(float x, float y);
  void			setPosition(sf::Vector2f pos);
  int			inRect(class Window &window);
  sf::Vector2i		getSize(void);
};

class			Window
{
public :
  sf::RenderWindow	win;
  sf::Vector2i		mouse;
  sf::Uint8		*pixels = NULL;
  sf::Texture		texture;
  sf::Sprite		sprite;
  sf::Event		event;
  sf::Font		font;
  bool			focus;

  ~Window();
  int			inRect(sf::Vector2f origin, sf::Vector2f size);
  void			close(void);
  void			create(int width, int height, std::string title,
			       std::string font_name, sf::Uint32 style);
  int			putPixel(sf::Vector2f pos, sf::Color color);
  int			putSquare(sf::Vector2i pos, sf::Color color, int size);
  void			drawLine(sf::Vector2f from, sf::Vector2f to, sf::Color color);
  void			pixel_buffer(int width, int height);
  sf::Vector2u		getSize(void);
  sf::Vector2i		getMouse(void);
  void			setPixels_color(sf::Color color);
  void			refreshPixels(void);
  void			refresh(void);
  void			clear(void);
  void			clear(sf::Color color);
  void			draw(sf::Sprite &sprite);
  void			draw(t_sprite &sprite);
  void			draw(t_sprite &sprite, sf::Vector2f pos);
  int			isOpen(void);
  void			freePixels(void);
  void			putWord(std::string word, sf::Vector2f pos, sf::Color color, int size);
  int			isClose(void);
  bool			isFocused(void);
};

class Button
{
public :
  t_sprite      sprite;
  t_sprite      onRect;
  t_sprite      onClick;
  std::string   name;
  int           status;
  Window        *win;

  void		setScale(double x, double y);
  void		setScale(sf::Vector2f size);
  void          create(std::string image, std::string name, Window *linked_win);
  void          addClickRect(std::string click, std::string rect);
  int           inRect(void);
  int           Click(void);
  int           Release(void);
  void          setPosition(sf::Vector2i pos);
  void          setPosition(sf::Vector2f pos);
  void          setPosition(float x, float y);
  sf::Vector2i  getPosition(void);
  sf::Vector2i  getSize(void);
  void          drawName(int size, sf::Color color);
  void          draw(int size, sf::Color color);
  void          draw(void);
};

int			keyReleased(sf::Keyboard::Key);

#endif /* !MY_SFML_HPP */
