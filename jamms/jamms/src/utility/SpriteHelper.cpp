#include <SpriteHelper.h>
#include <iostream>

sf::Sprite SpriteHelper::createSprite(std::string file_name) {
  sf::Texture texture;
  if(texture.loadFromFile(file_name) != true)
    std::cout << "File could not be loaded."; //Should throw error 

  sf::Sprite sprite;
  sprite.setTexture(texture);
  return sprite;
}