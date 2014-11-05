#pragma once
#include <gameObjects/Projectile.h>
#include <Player.h>
#define _USE_MATH_DEFINES
#include <math.h>

Projectile::Projectile() {
}

Projectile::Projectile(sf::Vector2f tower_position, sf::Vector2f critter_position) : _tower_position(tower_position), _critter_position(critter_position) {
	
	//this->_speed = Tower::RateOfFire::Slow * 2.0f;
	//this->_speed = rate_of_speed * 2.0f;

	Animation animation1(0, 4, 0.5f);
	Animation animation2(0, 4, 0.5f);
	std::vector<Animation> animations;
	animations.push_back(animation1);
	animations.push_back(animation2);
	initializeProjectile(animations);
}

Projectile::~Projectile() {
}

void Projectile::initializeProjectile(const std::vector<Animation>& animations) {

	this->_collision_path = this->_critter_position - this->_tower_position;
	// Set Projectile texture
	TextureManager& t_manager = TextureManager::getInstance();
	this->sprite.setTexture(t_manager.loadTexture("resources/images/ProjectileSpriteSheet.png"));

	/* Set up the initial animation */
	this->animation_handler.frame_size = sf::IntRect(0, 0, 32, 32); 

	//Add animations set in the constructor to handler
	for (auto animation : animations) {
		this->animation_handler.addAnimation(animation);
	}
	this->animation_handler.update(0.0f);   //Initial delta_time is 0
}

void Projectile::update() {

}

void Projectile::draw(sf::RenderWindow& game_window, float delta_time) {
  // Change the animation to reflect the current one
  this->animation_handler.changeAnimation(this->_animation_index);
  
  // Update the animation
  this->animation_handler.update(delta_time);

  // Set texture bounds for sprite
  this->sprite.setTextureRect(this->animation_handler.bounding_rect);

  //Set position for drawn sprite
  sprite.setPosition(this->getPosition());

  //Reset origin for drawn sprite
  sprite.setOrigin(16, 16);

  //Draw the sprite
  game_window.draw(this->sprite);
}

float Projectile::getRateOfFire() const {
	return _rate_of_fire;
}

//Tower::SpecialEffect Tower::getSpecialEffet() const {
//	return _special_effect;
//}

sf::Vector2f Projectile::getTowerPosition() const {
	return this->_tower_position;
}

sf::Vector2f Projectile::getCritterPosition() const {
	return this->_critter_position;
}

sf::Vector2f Projectile::getCollisionPath() const {
	return this->_collision_path;
}


void Projectile::setSpeed(float rate_of_fire) {
	this->time = this->clock.getElapsedTime();

	if(time.asSeconds() * this->getRateOfFire() >= 1)
		clock.restart();
	
	
	//switch(rate_of_fire) {
	//case Tower::RateOfFire::Slow:
	//case Tower::RateOfFire::Normal:
	//case Tower::RateOfFire::Fast:
	//	multiplier = 1.0;
	//	break;
	//}
	//this->_speed = rate_of_fire * multiplier;
}


/** 
  * @brief Determines collision path based on position of tower object and the distance in a straight line towards critter 
  * @return sf::Vector2f
  */
sf::Vector2f Projectile::findCollisionPath(Critter* critter) {
	return sf::Vector2f (this->_collision_path = critter->getPosition() - this->_tower_position);
}

void Projectile::move(sf::Vector2f collision_path){
}
//
//void Projectile::projectileSpeed(const sf::Vector2f &collision_path) {
//	sf::Vector2f normalVector = this->normalizeVector(collision_path);
//
//	switch(this->_Speed){
//	case SLOW:
//		normalVector = normalVector * 1.0f;
//		//normalVector = normalVector * int value of enum SLOW;
//		break;
//	case MEDIUM:
//		normalVector = normalVector * 2.0f;
//		break;
//	case FAST:
//		normalVector = normalVector * 3.0f;
//		break;
//	}
//}

/**
  * @brief Create unit vector
  * @return sf::Vector2f
  */
sf::Vector2f Projectile::normalizeVector(sf::Vector2f vector) const{
	return vector / sqrt((vector.x * vector.x) + (vector.y * vector.y));
}

void Projectile::setRotation(Critter* critter) {

	float facingCritterAngle = this->angle(this->_collision_path.x, this->_collision_path.y);
	this->sprite.setRotation(facingCritterAngle);

	//sprite.setRotation(this->collisionPath(critter)->angleBetween(0));
}

/**
  * @brief Calculates angle between an x and y component in degrees from the horizontal
  * @return float
  */
float Projectile::angle(float x, float y) {
	return std::atan2(x, y) * 180 / M_PI;
}