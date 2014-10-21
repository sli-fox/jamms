#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <views/Menu.h>
#include <list>
#include <managers/TextureManager.h>

class MainMenu: public Menu {
  public:
    Menu::MenuAction show(sf::RenderWindow& window);
    Menu::MenuAction Menu::getMenuResponse(sf::RenderWindow& window);
};