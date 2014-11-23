#include "GameObjects/ShihTzu.h"

int ShihTzu::serial = 0;
int const ShihTzu::buy_cost = 50;

ShihTzu::ShihTzu(int tileX, int tileY) {
	this->load("resources/images/towers/ShihTzu_0.png");
	this->setPosition(tileX*32, tileY*32);		// has to be set BEFORE setRange();

	this->_id = ShihTzu::serial++;
	this->_name = "ShihTzu_" + std::to_string(this->_id);
	this->_type = Tower::ShihTzu;
	this->_buy_cost = buy_cost;
	this->_power = 1;
	this->setRange(1);
	this->_rate_of_fire = Tower::RateOfFire::Normal;
	this->_special_effect = Tower::SpecialEffect::None;
	this->_upgrade_cost = 20;
	this->_sell_cost = 20;

	std::cout << green << this->_name << " has been created." << std::endl;
}

void ShihTzu::upgradeTower() {
	if(this->_upgrade_cost <= Game::player.getCash()) {
		int oldUpgradeCost = this->_upgrade_cost;
		if(this->getUpgradeLevel() == 0) {
			this->setUpgradeLevel(UpgradeLevel::Upgrade1);
			this->load("resources/images/towers/ShihTzu_1.png");
			this->setPower(1);
			this->setRange(1.5);
			this->setRateOfFire(Tower::RateOfFire::Normal);
			this->setSpecialEffect(Tower::SpecialEffect::None);
			this->setUpgradeCost(30);
			this->setSellCost(30);
		}
		else if(this->getUpgradeLevel() == 1) {
			this->setUpgradeLevel(UpgradeLevel::Upgrade2);
			this->load("resources/images/towers/ShihTzu_2.png");
			this->setPower(2);
			this->setRange(2);
			this->setRateOfFire(Tower::RateOfFire::Normal);
			this->setSpecialEffect(Tower::SpecialEffect::Slowing);
			this->setSellCost(40);
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