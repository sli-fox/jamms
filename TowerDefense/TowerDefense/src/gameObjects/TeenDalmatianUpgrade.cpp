#pragma once
#include <GameObjects/TeenDalmatianUpgrade.h>

int TeenDalmatianUpgrade::teen_upgrade_cost = 20;

TeenDalmatianUpgrade::TeenDalmatianUpgrade() {
	std::cout << green << "TeenDalmatianUpgrade Default Constructor called." << std::endl;
}

TeenDalmatianUpgrade::TeenDalmatianUpgrade(Tower* tower) : _decoratedTower(tower) {
	tower->load("resources/images/towers/Dalmatian_2.png");
	tower->setName("TeenDalmatian_"+ std::to_string(tower->getID()));
	tower->setRange(tower->getRange()+0.5);
	tower->setUpgradeLevel(Tower::UpgradeLevel::Teen);
	std::cout << green << tower->getName() << " has grown up to Teen." << std::endl;
}

int TeenDalmatianUpgrade::getBuyCost() const {
	return _decoratedTower->getBuyCost() + 20;
}

void TeenDalmatianUpgrade::setRange(float _range) {
	this->_range = _range;
	this->setRangeShape(_range);
	_decoratedTower->setRange(_range);
}

/**
  * @brief Determines whether tower can attack a critter based on whether the critter falls within its range while taking into account the tower's rate of fire delay
  * @return bool
  */
bool TeenDalmatianUpgrade::canAttack(Critter* critter) {
	return _decoratedTower->canAttack(critter);
}

void TeenDalmatianUpgrade::attack() {
		this->_target = _decoratedTower->getTarget();
		_decoratedTower->attack();
		std::cout << yellow << this->_name << " attacking..." << std::endl;
}

// @Override
std::string TeenDalmatianUpgrade::getTowerSpecs() {
	std::stringstream output;
	output << _decoratedTower->getTowerSpecs() << std::endl;
	return output.str();
}