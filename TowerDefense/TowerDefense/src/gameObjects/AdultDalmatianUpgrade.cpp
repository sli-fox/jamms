#pragma once
#include <GameObjects/AdultDalmatianUpgrade.h>

int AdultDalmatianUpgrade::adult_upgrade_cost = 30;

AdultDalmatianUpgrade::AdultDalmatianUpgrade() {
	std::cout << green << "AdultDalmatianUpgrade Default Constructor called." << std::endl;
}

AdultDalmatianUpgrade::AdultDalmatianUpgrade(Tower* tower) : _decoratedTower(tower) {
	tower->load("resources/images/towers/Dalmatian_2.png");
	tower->setName("AdultDalmatian_"+ std::to_string(tower->getID()));
	tower->setRange(tower->getRange()+0.5);
	tower->setUpgradeLevel(Tower::UpgradeLevel::Adult);
	std::cout << green << tower->getName() << " has grown up to Adult." << std::endl;
}

int AdultDalmatianUpgrade::getBuyCost() const {
	return _decoratedTower->getBuyCost() + 20;
}

void AdultDalmatianUpgrade::setRange(float _range) {
	this->_range = _range;
	this->setRangeShape(_range);
	_decoratedTower->setRange(_range);
}

/**
  * @brief Determines whether tower can attack a critter based on whether the critter falls within its range while taking into account the tower's rate of fire delay
  * @return bool
  */
bool AdultDalmatianUpgrade::canAttack(Critter* critter) {
	return _decoratedTower->canAttack(critter);
}

void AdultDalmatianUpgrade::attack() {
		this->_target = _decoratedTower->getTarget();
		_decoratedTower->attack();
		std::cout << yellow << this->_name << " attacking..." << std::endl;
}

// @Override
std::string AdultDalmatianUpgrade::getTowerSpecs() {
	std::stringstream output;
	output << _decoratedTower->getTowerSpecs() << std::endl;
	return output.str();
}