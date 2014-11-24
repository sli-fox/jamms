#include "GameObjects/ConcreteTower.h"

int ConcreteTower::serial = 0;
int const ConcreteTower::upgrade_range_cost = 10;

int ConcreteTower::getBuyCost() const {
	return _buy_cost;
}

void ConcreteTower::setRange(float _range) {
	this->_range = _range;
	this->setRangeShape(_range);
}

void ConcreteTower::attack() {
	std::cout << yellow << this->_name << " attacking #" << this->_target->getId() << "... ";
	this->_target->inflictDamage(this->getPower());
	std::cout << yellow << this->_target->getHitPoints() << "HP" << std::endl;
}

/**
  * @brief Determines whether tower can attack a critter based on whether the critter falls within its range while taking into account the tower's rate of fire delay
  * @return bool
  */
bool ConcreteTower::canAttack(Critter* critter) { //@MARK canAttack() is performing 3 functions. range checking, attack timer checking, and target selection. we should split them into 3 methods in my opinion -Jeremy-
	
	if(!this->_target == NULL && (!this->circleToCircleIntersection(_target) || !_target->isActive))
		this->_target = NULL;

	if(this->_target == NULL) {
		_target = critter;
		//this->rotateTowardsTarget();
	}
	else{
		_target = executeStrategy(critter);
		//_target = critter;
		// I changed them to be more consistent -Jeremy-
	}

	this->time = this->clock.getElapsedTime();
	
	if(this->circleToCircleIntersection(_target) && time.asSeconds()*this->getRateOfFire() >= 1){
		clock.restart();
		return true;
	}

	return false;
}

std::string ConcreteTower::getTowerSpecs() {
	//Since we can't cout an enum in C++, we need this Array system as a workaround (optional, but prettier at output)
	char *UpgradeLevelA[] = { "Baby", "Teen", "Adult" };
	char *RateOfFireA[] = { "Slow", "Normal", "Fast" };
	char *SpecialEffectA[] = { "None", "Slowing", "Burning", "Freezing" };
	std::stringstream output;
	output << "CURRENT TOWER SPECIFICATIONS:" << std::endl;
	output << "Name: " << this->_name << std::endl;
	output << "Upgrade: " << UpgradeLevelA[this->_upgrade_level] << std::endl;
	output << "Power: " << this->_power << std::endl;
	output << "Range:  " << this->_range << std::endl;
	output << "Fire Rate: " << RateOfFireA[this->_rate_of_fire-1] << std::endl;
	output << "Buy Cost: " << this->getBuyCost() << " coins" << std::endl;
	output << "Upgrade Cost: " << this->_upgrade_cost << " coins" << std::endl;
	output << "Sell Cost: " << this->_sell_cost << " coins" << std::endl;

	return output.str();
}