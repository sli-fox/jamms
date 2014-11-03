#pragma once
#include "GameObject.h"
#include <SFML\Graphics\Transformable.hpp>
#include <gameObjects/Critter.h>
#include "Tower.h"
#include <utils/Animation.h>
#include <utils/AnimationHandler.h>

class Projectile : public GameObject {

public:

	//enum Speed {SLOW, MEDIUM, FAST};
	//enum ProjectileType {REDUCED_STRENGTH, REGULAR_STRENGTH, EXTRA_STRENGTH, NORMAL, FIERY, FREEZING, REDUCED_SPEED, INCREASED_SPEED};

	AnimationHandler animation_handler;

	// Constructors and Destructors
	Projectile();
	//Projectile(sf::Vector2f initial_position, int power, Tower::RateOfFire rate_of_fire, Tower::SpecialEffect special_effect);
	virtual ~Projectile();

	// Accessor Methods
	std::string getName() const;
	int getDamage() const;
	//Speed getSpeed() const;
	//ProjectileType getProjectileType() const;
	sf::Vector2f getCollisionPath() const;

	sf::Vector2f findCollisionPath(Critter* critter);
	void collision(Critter* critter);
	virtual void move(sf::Vector2f collision_path);
	void projectileSpeed(const sf::Vector2f &collisionPath);
	virtual void setRotation(Critter* critter);
	sf::Vector2f normalizeVector(sf::Vector2f vector) const;
	float angle(float x, float y);

private:

	std::string _name;
	int _damage; //damage attribute is taken from the tower
	Tower::RateOfFire _rate_of_fire;
	//Speed _Speed;
	//ProjectileType _Projectile_Type;
	sf::Vector2f _initial_position;
	sf::Vector2f _collision_path;

	virtual void initializeProjectile(const std::vector<Animation>& animations);
};