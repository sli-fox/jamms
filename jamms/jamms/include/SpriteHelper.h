#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class SpriteHelper {
  public:
    static sf::Sprite createSprite(std::string file_name);
};