#include "WhiteBloodCellTower.h"

int WhiteBloodCellTower::serial = 0;
int const WhiteBloodCellTower::buy_cost = 50;

WhiteBloodCellTower::WhiteBloodCellTower(sf::Vector2i mousePos) {
	this->_id = WhiteBloodCellTower::serial++;
	this->_name = "WhiteBloodCellTower_" + std::to_string(this->_id);
	this->_type = Tower::WhiteBloodCellTower;
	this->_power = 1;
	this->_range = Tower::Range::Small;
	this->_rate_of_fire = Tower::RateOfFire::Slow;
	this->_special_effect = Tower::SpecialEffect::None;
	this->_upgrade_cost = 20;
	this->_sell_cost = 10;

	this->load("resources/images/towers/WhiteBloodCellTower_0.png");
	// setting towers in blocks of 32 pixels only
	mousePos.x = (int)mousePos.x/32*32;
	mousePos.y = (int)mousePos.y/32*32;
	this->setPosition(mousePos.x, mousePos.y);
	
	std::cout << green << this->_name << " has been created." << std::endl;
}

void WhiteBloodCellTower::upgradeTower() {
	if(this->_upgrade_cost <= getWallet()) {
		int oldUpgradeCost = this->_upgrade_cost;
		if(this->getUpgradeLevel() == 0) {
			this->setPower(2);
			this->setRange(Tower::Range::Medium);
			this->setRateOfFire(Tower::RateOfFire::Normal);
			this->setUpgradeCost(30);
			this->setSellCost(20);
			this->setUpgradeLevel(UpgradeLevel::Upgrade1);
			this->load("resources/images/towers/WhiteBloodCellTower_1.png");
		}
		else if(this->getUpgradeLevel() == 1) {
			this->setPower(3);
			this->setRange(Tower::Range::Large);
			this->setRateOfFire(Tower::RateOfFire::Fast);
			this->setSellCost(30);
			this->setUpgradeLevel(UpgradeLevel::Upgrade2);
			this->load("resources/images/towers/WhiteBloodCellTower_2.png");
		}
		else {
			std::cout << red << "Error: Tower already fully upgraded." << std::endl;
			return;
		}
		updateWallet(- oldUpgradeCost);
		std::cout << blue << "Tower successfully upgraded for " << oldUpgradeCost << " coins." << std::endl;
	} else {
		std::cout << red << "Insufficient funds" << std::endl;
	}
}