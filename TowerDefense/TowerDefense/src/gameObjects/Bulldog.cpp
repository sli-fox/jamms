#include "GameObjects/Bulldog.h"

int Bulldog::serial = 0;
int const Bulldog::buy_cost = 70;

Bulldog::Bulldog(int tileX, int tileY) {
	this->_id = Bulldog::serial++;
	this->_name = "Bulldog_" + std::to_string(this->_id);
	this->_type = Tower::Bulldog;
	this->_range_shape.setPosition((tileX*32)-16, (tileY*32)-16);
	this->_buy_cost = buy_cost;
	this->_power = 2;
	this->_range = Tower::Range::Small;
	this->setRangeShape(_range);
	this->_rate_of_fire = Tower::RateOfFire::Slow;
	this->_special_effect = Tower::SpecialEffect::None;
	this->_upgrade_cost = 20;
	this->_sell_cost = 30;
	
	this->load("resources/images/towers/bulldog_0.png");
	this->setPosition(tileX*32, tileY*32);
	
	std::cout << green << this->_name << " has been created." << std::endl;
}

void Bulldog::upgradeTower() {
	if(this->_upgrade_cost <= Game::player.getCash()) {
		int oldUpgradeCost = this->_upgrade_cost;
		if(this->getUpgradeLevel() == 0) {
			this->setRangeShape(_range);
			this->setUpgradeLevel(UpgradeLevel::Upgrade1);
			this->load("resources/images/towers/bulldog_1.png");
			this->setPower(3);
			this->setRange(Tower::Range::Small);
			this->setRateOfFire(Tower::RateOfFire::Normal);
			this->setSpecialEffect(Tower::SpecialEffect::None);
			this->setUpgradeCost(20);
			this->setSellCost(40);
		}
		else if(this->getUpgradeLevel() == 1) {
			this->setRangeShape(_range);
			this->setUpgradeLevel(UpgradeLevel::Upgrade2);
			this->load("resources/images/towers/bulldog_2.png");
			this->setPower(4);
			this->setRange(Tower::Range::Small);
			this->setRateOfFire(Tower::RateOfFire::Normal);
			this->setSpecialEffect(Tower::SpecialEffect::None);
			this->setSellCost(50);
		}
		else {
			std::cout << red << "Error: Tower already fully upgraded." << std::endl;
			return;
		}
		Game::player.spendCash(oldUpgradeCost);
		std::cout << blue << "Tower successfully upgraded for " << oldUpgradeCost << " coins." << std::endl;
	} else {
		std::cout << red << "Insufficient funds" << std::endl;
	}
}