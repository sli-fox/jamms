#include <gameObjects/GameObject.h>

/**  @brief The GameObject constructor.
  *  Default setup is the sprite has not been created. 
  */
GameObject::GameObject() : isSpriteCreated(false) {}

/**  load() gets a reference to the TextureManager instance, loads
  *  the texture based on the given file name, sets the texture 
  *  for the GameObject sprite, and indicates that the sprite
  *  creation is true.
  */
void GameObject::load(std::string file_name) {
  TextureManager& t_manager = TextureManager::getInstance();
  sprite.setTexture(t_manager.loadTexture(file_name));
  isSpriteCreated = true;
}

/**  draw() takes in a reference to a rendering window and checks
  *  if sprite is created, if it has been, the sprite is drawn to 
  *  the window.
  */
void GameObject::draw(sf::RenderWindow& render_window) {
  if (isSpriteCreated) {
    render_window.draw(this->sprite);
  }
}

/**  setPosition() sets x and y coordinates of the sprite if it has
  *  been created. 
  */
void GameObject::setPosition(float x, float y) {
  if (isSpriteCreated) {
    sprite.setPosition(x, y);
  }
}

  sf::Vector2f GameObject::getPosition() const{
	  return sprite.getPosition();
  }

  std::string GameObject::getFileName() const{
	  return file_name;
  }

  bool GameObject::spriteContains(sf::Vector2i position) const{
	  return sprite.getGlobalBounds().contains(float(position.x), float(position.y));
  }