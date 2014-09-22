#include <GameObject.h>

GameObject::GameObject() : _isSpriteCreated(false) {}

void GameObject::load(std::string file_name) {
  TextureManager& t_manager = TextureManager::getInstance();
  sf::Sprite _sprite(t_manager.loadTexture(file_name));
  _isSpriteCreated = true;
}

void GameObject::draw(sf::RenderWindow& render_window) {
  if (_isSpriteCreated) {
    render_window.draw(_sprite);
  }
}

void GameObject::setPosition(float x, float y) {
  if (_isSpriteCreated) {
    _sprite.setPosition(x, y);
  }
}
