#pragma once
#include "gameObjects/Towers/TowerDecorator.h"

Dec::TowerDecorator::TowerDecorator(ITower* decoratedTower) : _decoratedTower(decoratedTower)  {
	this->_power = 2;
	this->_speed = 5;
	this->_range = 32;
	this->load("resources/images/dead.png");
	this->setPosition(decoratedTower->getPosition().x, decoratedTower->getPosition().y);
}

// ACCESSORS
int Dec::TowerDecorator::getPower() const {
	return _power;
}
int Dec::TowerDecorator::getSpeed() const {
	return _speed;
}
float Dec::TowerDecorator::getRange() const {
	return _range;
}

// MUTATORS
void Dec::TowerDecorator::setPower(int power) {
	this->_power = power;
}
void Dec::TowerDecorator::setSpeed(int speed) {
	this->_speed = speed;
}
void Dec::TowerDecorator::setRange(float range) {
	this->_range = range;
}

// @Override
std::string Dec::TowerDecorator::getTowerSpecs() {
	_decoratedTower->getTowerSpecs();
	std::stringstream output;
	output << "Power: " << this->_power << std::endl;
	output << "Speed: " << this->_speed << std::endl;
	output << "Range: " << this->_range << std::endl;
	std::cout << blue << output.str() << std::endl;
	return output.str();
}