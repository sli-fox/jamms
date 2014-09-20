#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <list>
#include <TextureManager.h>

class Menu {
  public:
    enum MenuAction { Nothing, Play, Exit };

    struct MenuItem {
      public:
        sf::IntRect rect;
        MenuAction action;
    };

    virtual MenuAction show(sf::RenderWindow& window) = 0;

  protected:
    virtual MenuAction getMenuResponse(sf::RenderWindow& window) = 0;
    MenuAction handleClick(int x, int y);
    std::list<MenuItem> _menu_items;
};