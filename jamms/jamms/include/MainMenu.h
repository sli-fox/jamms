#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <list>

class MainMenu {
  public:
    enum MenuItemAction { Nothing, Exit, Play };

    //If we have multiple menus, then MainMenu should
    //dervive from a common base Menu class and
    //consist of generic MenuItem class
    struct MenuItem {
      public:
        sf::Rect<int> menu_item_rect;
        MenuItemAction action;
    };

    MenuItemAction Show(sf::RenderWindow& window);

  private:
    MenuItemAction GetMenuResponse(sf::RenderWindow& window);
    MenuItemAction HandleClick(int x, int y);
    std::list<MenuItem> menu_items_;
};