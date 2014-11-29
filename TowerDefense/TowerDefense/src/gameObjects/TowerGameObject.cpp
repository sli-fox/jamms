#include <gameObjects/TowerGameObject.h>

TowerGameObject::TowerGameObject() {
  this->time = clock.getElapsedTime();
}

sf::CircleShape TowerGameObject::getRangeShape() const {
  return _range_shape;
}
void TowerGameObject::setRateOfFire(TowerGameObject::RateOfFire _rate_of_fire) {
  this->_rate_of_fire = _rate_of_fire;
}

void TowerGameObject::setRangeShape(float range) {
  range *= 32;
  _range_shape.setPosition(this->getPosition().first, this->getPosition().second);
  _range_shape.setRadius(range);
  _range_shape.setFillColor(sf::Color::Transparent);
  _range_shape.setOutlineThickness(2);
  _range_shape.setOutlineColor(sf::Color::Red);
  _range_shape.setOrigin(range-16, range-16);
}
TowerGameObject::RateOfFire TowerGameObject::getRateOfFire() const {
  return _rate_of_fire;
}

Critter* TowerGameObject::getTarget() const {
  return _target;
}

void TowerGameObject::setTarget(Critter* crit) {
  this->_target = crit;
}

/**
* @brief Determines whether tower can apply a special effect on a critter based on whether the critter falls within its range while taking into account the tower's rate of fire delay
* @return bool
*/
bool TowerGameObject::canApplySpecialAfterEffects(Critter* critter) {
  this->time = this->clock.getElapsedTime();

  if(this->circleToCircleIntersection(critter) && time.asSeconds()*this->getRateOfFire() >= 1) {
    clock.restart();
    return true;
  }
  return false;
}

/**
* @brief Overrides method to apply to tower range sf::CircleShape object
* @return bool
*/
bool TowerGameObject::circleToCircleIntersection(GameObject* game_object){
  float radius = this->_range_shape.getRadius();

  std::pair <int, int> distance (this->getSpriteCenter().first - game_object->getSpriteCenter().first, this->getSpriteCenter().second - game_object->getSpriteCenter().second);  

  return std::sqrt(std::pow(distance.first, 2) + std::pow(distance.second, 2)) <= radius;
}

Critter* TowerGameObject::executeStrategy(Critter* critter){
	return this->_strategy->computeTarget(critter, _target, getPosition());
}

/**
* @brief Determines whether tower can attack a critter based on whether the critter falls within its range while taking into account the tower's rate of fire delay
* @return bool
*/
bool TowerGameObject::canAttack(Critter* critter) { //@MARK canAttack() is performing 3 functions. range checking, attack timer checking, and target selection. we should split them into 3 methods in my opinion -Jeremy-

  if(!this->_target == NULL && (!this->circleToCircleIntersection(_target) || !_target->isActive))
    this->_target = NULL;

  if(this->_target == NULL) {
    _target = critter;
    //this->rotateTowardsTarget();
  }
  else{
    _target = executeStrategy(critter);
  }

  this->time = this->clock.getElapsedTime();

  if(this->circleToCircleIntersection(_target) && time.asSeconds()*this->getRateOfFire() >= 1){
    clock.restart();
    return true;
  }

  return false;
}
