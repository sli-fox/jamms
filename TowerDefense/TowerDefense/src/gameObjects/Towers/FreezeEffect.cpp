#pragma once
#include <GameObjects/Towers/FreezeEffect.h>

Dec::FreezeEffect::FreezeEffect() {
	std::cout << green << "Default Constructor called." << std::endl;
}

Dec::FreezeEffect::FreezeEffect(ITower* decoratedTower) : _decoratedTower(decoratedTower) {
	this->_effect = "Freezing Critter";
	this->load("resources/images/end.png");
	this->setPosition(decoratedTower->getPosition().first, decoratedTower->getPosition().second);
}

int Dec::FreezeEffect::getBuyCost() const {
	return 0;
}

// @Override
std::string Dec::FreezeEffect::getTowerSpecs() {
	_decoratedTower->getTowerSpecs();
	std::stringstream output;
	output << "Special Effect: " << this->_effect << std::endl;
	std::cout << blue << output.str() << std::endl;
	return output.str();
}