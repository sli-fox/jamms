#pragma once
#include "GameObject.h"
#include <SFML\Graphics\Transformable.hpp>
#include <gameObjects/Critter.h>
#include "Tower.h"
#include <utils/Animation.h>
#include <utils/AnimationHandler.h>


class Projectile : public GameObject {

public:

	Projectile();
	Projectile(sf::Vector2f tower_position, sf::Vector2f critter_position);
	virtual ~Projectile();

	std::string getName() const;
	int getPower() const;
	float getRateOfFire() const;
	//Tower::SpecialEffect getSpecialEffet() const;
	sf::Vector2f getTowerPosition() const;
	sf::Vector2f getCritterPosition() const;
	sf::Vector2f getCollisionPath() const;

	void setSpeed(float rate_of_fire);

	virtual void update();
	virtual void draw(sf::RenderWindow& game_window, float delta_time);
	sf::Vector2f findCollisionPath(Critter* critter);
	virtual void move(sf::Vector2f collision_path);
	void projectileSpeed(const sf::Vector2f &collisionPath);
	virtual void setRotation(Critter* critter);
	sf::Vector2f normalizeVector(sf::Vector2f vector) const;
	float angle(float x, float y);

	AnimationHandler animation_handler;

private:

	float _speed;
	float _rate_of_fire;
	//Tower::SpecialEffect _special_effect;
	int _animation_index;
	sf::Vector2f _tower_position;
	sf::Vector2f _critter_position;
	sf::Vector2f _collision_path;

	sf::Clock clock;
	sf::Time time;

	virtual void initializeProjectile(const std::vector<Animation>& animations);
};