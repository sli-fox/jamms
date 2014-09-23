#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <TextureManager.h>

class GameObject {
  public:
    GameObject();
    virtual ~GameObject() {}

    virtual void load(std::string file_name);
    virtual void draw(sf::RenderWindow& window);

    virtual void setPosition(float x, float y);

  private:
    sf::Sprite _sprite;
    std::string _file_name;
    bool _isSpriteCreated;
};
