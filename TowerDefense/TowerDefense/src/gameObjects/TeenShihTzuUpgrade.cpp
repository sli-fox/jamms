#pragma once
#include <GameObjects/TeenShihTzuUpgrade.h>

int TeenShihTzuUpgrade::teen_upgrade_cost = 20;

TeenShihTzuUpgrade::TeenShihTzuUpgrade() {
	std::cout << green << "TeenShihTzuUpgrade Default Constructor called." << std::endl;
}

TeenShihTzuUpgrade::TeenShihTzuUpgrade(Tower* tower) : _decoratedTower(tower) {
	tower->load("resources/images/towers/ShihTzu_1.png");
	tower->setName("TeenShihTzu_"+ std::to_string(tower->getID()));
	tower->setRange(tower->getRange()+0.5);
	tower->setUpgradeLevel(Tower::UpgradeLevel::Teen);
	std::cout << green << tower->getName() << " has grown up to Teen." << std::endl;
}

int TeenShihTzuUpgrade::getBuyCost() const {
	return _decoratedTower->getBuyCost() + 20;
}

void TeenShihTzuUpgrade::setRange(float _range) {
	this->_range = _range;
	this->setRangeShape(_range);
	_decoratedTower->setRange(_range);
}

/**
  * @brief Determines whether tower can attack a critter based on whether the critter falls within its range while taking into account the tower's rate of fire delay
  * @return bool
  */
bool TeenShihTzuUpgrade::canAttack(Critter* critter) {
	return _decoratedTower->canAttack(critter);
}

void TeenShihTzuUpgrade::attack() {
		this->_target = _decoratedTower->getTarget();
		_decoratedTower->attack();
		std::cout << yellow << this->_name << " attacking..." << std::endl;
}

// @Override
std::string TeenShihTzuUpgrade::getTowerSpecs() {
	std::stringstream output;
	output << _decoratedTower->getTowerSpecs() << std::endl;
	return output.str();
}