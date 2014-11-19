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

/**
  * @brief Converts and retrieves an pair<float, float> object from a sf::vector2f
  * @return std::pair<float, float>
  */
  std::pair<float, float> GameObject::getPosition() const{
	  return std::pair<float, float> (this->sprite.getPosition().x, this->sprite.getPosition().y);
  }

  std::string GameObject::getFileName() const{
	  return file_name;
  }

  bool GameObject::spriteContains(sf::Vector2i position) const{
	  return sprite.getGlobalBounds().contains(float(position.x), float(position.y));
  }

void GameObject::setRotation(float angle) {
	this->sprite.setRotation(angle);
}

void GameObject::move(float x, float y) {
	this->move(sf::Vector2f (x,y));
}

void GameObject::move(const sf::Vector2f &offset){
	this->sprite.move(offset);
}

 /**
  * @brief Retrieves the floating recantle encompassing a sprite (after the result of transormations)
  * @return sf::FloatRect
  */
sf::FloatRect GameObject::getGlobalBounds() const {
	return this->sprite.getGlobalBounds();
}

 /**
  * @brief Bouding box intersection between GameObjects
  * @return bool
  */
bool GameObject::boxToBoxIntersection(GameObject* game_object) {
	return this->getGlobalBounds().intersects(game_object->getGlobalBounds());
}

 /**
  * @brief Measures the distance between the centers of each object to each other and compare that with their radii
  * @return bool
  */
bool GameObject::circleToCircleIntersection(GameObject* game_object) {
	float radius_1 = this->getRectangleSpriteRadius();
	float radius_2 = game_object->getRectangleSpriteRadius();

	std::pair <int, int> distance (this->getSpriteCenter().first - game_object->getSpriteCenter().first, this->getSpriteCenter().second - game_object->getSpriteCenter().second);  

	return std::sqrt(std::pow(distance.first, 2) + std::pow(distance.second, 2)) <= (radius_1 + radius_2);
}

 /**
  * @brief Measures the radius of the rectangle sprite
  * @return bool
  */
float GameObject::getRectangleSpriteRadius() {
	std::pair<float, float> size = this->getSpriteSize();
	return (size.first + size.second) * 2.5; // originally divided by 4. changed to get slightly more "accurate" collision
}

 /**
  * @brief Gets the center of a sprite
  * @return std::pair<float, float>
  */
std::pair<float, float> GameObject::getSpriteCenter() {
	sf::FloatRect globalBounds = this->sprite.getGlobalBounds();
	return std::pair<float, float> (globalBounds.left + globalBounds.width / 2.0f, globalBounds.top + globalBounds.height / 2.0f);
}

 /**
  * @brief Gets the size of a sprite
  * @return std::pair<float, float>
  */
std::pair<float, float> GameObject::getSpriteSize() {
	sf::IntRect size = this->sprite.getTextureRect();
	sf::Vector2f scale = this->sprite.getScale();
	return std::pair<float, float> (size.width * scale.x, size.height * scale.y);
}