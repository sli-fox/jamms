#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Menu.h>
#include <list>
#include <TextureManager.h>

class MainMenu: public Menu {
public:
    Menu::MenuAction show(sf::RenderWindow& window);
};