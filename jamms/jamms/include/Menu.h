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
        sf::Rect<int> rect;
        MenuAction action;
    };

    virtual MenuAction show(sf::RenderWindow& window) =0;

  protected:
    MenuAction getMenuResponse(sf::RenderWindow& window);
    MenuAction handleClick(int x, int y);
    std::list<MenuItem> _menu_items;
};