#pragma once
#include <gameObjects/Projectile.h>
#include <Player.h>
#define _USE_MATH_DEFINES
#include <math.h>

//Projectile::Projectile(sf::Vector2f initial_position, int power, Tower::RateOfFire rate_of_fire, Tower::SpecialEffect special_effect) : _initial_position(initial_position), _damage(power) {


	/*
	// Set Projectile texture
	TextureManager& t_manager = TextureManager::getInstance();
	this->sprite.setTexture(t_manager.loadTexture("resources/images/test.png"));

	Animation animation1(0, 2, 0.5f);
	Animation animation2(0, 2, 0.5f);
	Animation animation3(0, 2, 0.5f);
	Animation animation4(0, 2, 0.5f);
	std::vector<Animation> animations;
	animations.push_back(animation1);
	animations.push_back(animation2);
	animations.push_back(animation3);
	animations.push_back(animation4);
	initializeProjectile(animations);*/
//}

Projectile::~Projectile(){
}

void Projectile::initializeProjectile(const std::vector<Animation>& animations) {

	///* Set up the initial animation */
	//// Note, pixels are hardcoded for now for the frame size
	//this->animation_handler.frame_size = sf::IntRect(0, 0, 32, 32); 

	////Add animations set in the constructor to handler
	//for (auto animation : animations) {
	//this->animation_handler.addAnimation(animation);
	//}
	//this->animation_handler.update(0.0f);   //Initial delta_time is 0
}


std::string Projectile::getName() const {
	return this->_name;
}

int Projectile::getDamage() const {
	return this->_damage;
}

//Projectile::Speed Projectile::getSpeed() const {
//	return this->_Speed;
//}
//
//Projectile::ProjectileType Projectile::getProjectileType() const {
//	return this->_Projectile_Type;
//}

sf::Vector2f Projectile::getCollisionPath() const {
	return this->_collision_path;
}

/**
  * @brief Once the critter comes in contact with or within the tower range, damage is received and other possible consequences follow such as death.
  * @return void
  */
void Projectile::collision(Critter* critter){
	if(this->circleToCircleIntersection(critter)) {
		if(critter->getHitPoints() > 0)
			critter->setHitPoints(critter->getHitPoints() - this->_damage);
		if(critter->getHitPoints() <= 0) {
			critter->setHitPoints(0);
			//delete critter;
			//player->earnCash(0/*cash for beating wave?*/);
			//player->gainPoints(critter->getPlayerReward());
		}
	}
	else {
		//doesnt collide with critter, projectile dissapears out of range
		std::cout << "MISSED THE TARGET!! " << std::endl;
		delete this;
	}
}

/** 
  * @brief Determines collision path based on position of tower object and the distance in a straight line towards critter 
  * @return sf::Vector2f
  */
sf::Vector2f Projectile::findCollisionPath(Critter* critter) {
	return sf::Vector2f (this->_collision_path = critter->getPosition() - this->_initial_position);
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

	this->angle(this->_collision_path.x, this->_collision_path.y);

	//this->sprite.setRotation(this->sprite.getRotation());

	//set rotation of the projectile sprite based on the angle formed between the collision path and horizon
	//sprite.setRotation(this->collisionPath(critter)->angleBetween(0));
}

/**
  * @brief Calculates angle between an x and y component in degrees from the horizontal
  * @return float
  */
float Projectile::angle(float x, float y) {
	return std::atan2(x, y) * 180 / M_PI;
}