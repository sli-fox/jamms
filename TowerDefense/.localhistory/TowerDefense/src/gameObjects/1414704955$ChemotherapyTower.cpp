#include "GameObjects/ChemotherapyTower.h"

int ChemotherapyTower::serial = 0;
int const ChemotherapyTower::buy_cost = 70;

ChemotherapyTower::ChemotherapyTower(int tileX, int tileY) {
	this->_id = ChemotherapyTower::serial++;
	this->_name = "ChemotherapyTower_" + std::to_string(this->_id);
	this->_type = Tower::ChemotherapyTower;
	this->_power = 1;
	this->_range = Tower::Range::Small;
	this->_rate_of_fire = Tower::RateOfFire::Slow;
	this->_special_effect = Tower::SpecialEffect::Slowing;
	this->_upgrade_cost = 20;
	this->_sell_cost = 30;
	
	this->load("resources/images/towers/ChemotherapyTower_0.png");
	this->setPosition(tileX*32, tileY*32);
	
	std::cout << green << this->_name << " has been created." << std::endl;
}

void ChemotherapyTower::upgradeTower() {
	if(this->_upgrade_cost <= getWallet()) {
		int oldUpgradeCost = this->_upgrade_cost;
		if(this->getUpgradeLevel() == 0) {
			this->setPower(2);
			this->setRange(Tower::Range::Medium);
			this->setRateOfFire(Tower::RateOfFire::Normal);
			this->setUpgradeCost(20);
			this->setSellCost(40);
			this->setUpgradeLevel(UpgradeLevel::Upgrade1);
			this->load("resources/images/towers/ChemotherapyTower_1.png");
		}
		else if(this->getUpgradeLevel() == 1) {
			this->setPower(3);
			this->setRange(Tower::Range::Large);
			this->setRateOfFire(Tower::RateOfFire::Fast);
			this->setSellCost(50);
			this->setUpgradeLevel(UpgradeLevel::Upgrade2);
			this->load("resources/images/towers/ChemotherapyTower_2.png");
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