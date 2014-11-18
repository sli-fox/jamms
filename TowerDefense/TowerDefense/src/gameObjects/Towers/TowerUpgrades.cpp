#pragma once
#include "gameObjects/Towers/TowerUpgrades.h"

// ACCESSORS
int TowerUpgrades::getPower() const {
	return power;
}
int TowerUpgrades::getSpeed() const {
	return speed;
}
TowerUpgrades::Range TowerUpgrades::getRange() const {
	return range;
}

// MUTATORS
void TowerUpgrades::setPower(int power) {
	this->power = power;
}
void TowerUpgrades::setSpeed(int speed) {
	this->speed = speed;
}
void TowerUpgrades::setRange(TowerUpgrades::Range range) {
	this->range = range;
}