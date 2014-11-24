#pragma once
#include <GameObjects/TeenBulldogUpgrade.h>

int TeenBulldogUpgrade::teen_upgrade_cost = 20;

TeenBulldogUpgrade::TeenBulldogUpgrade() {
	std::cout << green << "TeenBulldogUpgrade Default Constructor called." << std::endl;
}

TeenBulldogUpgrade::TeenBulldogUpgrade(Tower* tower) : _decoratedTower(tower) {
	tower->load("resources/images/towers/Bulldog_1.png");
	tower->setName("TeenBulldog_"+ std::to_string(tower->getID()));
	tower->setRange(tower->getRange()+0.5);
	tower->setUpgradeLevel(Tower::UpgradeLevel::Teen);
	std::cout << green << tower->getName() << " has grown up to Teen." << std::endl;
}

int TeenBulldogUpgrade::getBuyCost() const {
	return _decoratedTower->getBuyCost() + 20;
}

void TeenBulldogUpgrade::setRange(float _range) {
	this->_range = _range;
	this->setRangeShape(_range);
	_decoratedTower->setRange(_range);
}

/**
  * @brief Determines whether tower can attack a critter based on whether the critter falls within its range while taking into account the tower's rate of fire delay
  * @return bool
  */
bool TeenBulldogUpgrade::canAttack(Critter* critter) {
	return _decoratedTower->canAttack(critter);
}

void TeenBulldogUpgrade::attack() {
		this->_target = _decoratedTower->getTarget();
		_decoratedTower->attack();
		std::cout << yellow << this->_name << " attacking..." << std::endl;
}

// @Override
std::string TeenBulldogUpgrade::getTowerSpecs() {
	std::stringstream output;
	output << _decoratedTower->getTowerSpecs() << std::endl;
	return output.str();
}