#include "GameObjects/ShihTzu.h"

int ShihTzu::serial = 0;
int const ShihTzu::buy_cost = 50;

ShihTzu::ShihTzu(int tileX, int tileY) {
	this->_id = ShihTzu::serial++;
	this->_name = "ShihTzu_" + std::to_string(this->_id);
	this->_type = Tower::ShihTzu;
	this->_power = 1;
	this->_range = Tower::Range::Small;
	this->setRangeShape(_range);
	this->_range_shape.setPosition((tileX*32)-16, (tileY*32)-16);
	this->_rate_of_fire = Tower::RateOfFire::Slow;
	this->_special_effect = Tower::SpecialEffect::None;
	this->_upgrade_cost = 20;
	this->_sell_cost = 10;

	this->load("resources/images/towers/ShihTzu_0.png");
	this->setPosition(tileX*32, tileY*32);
	
	std::cout << green << this->_name << " has been created." << std::endl;
}

void ShihTzu::upgradeTower() {
	if(this->_upgrade_cost <= Game::player.getCash()) {
		int oldUpgradeCost = this->_upgrade_cost;
		if(this->getUpgradeLevel() == 0) {
			this->setPower(2);
			this->setRange(Tower::Range::Medium);
			this->setRangeShape(_range);
			this->setRateOfFire(Tower::RateOfFire::Normal);
			this->setUpgradeCost(30);
			this->setSellCost(20);
			this->setUpgradeLevel(UpgradeLevel::Upgrade1);
			this->load("resources/images/towers/ShihTzu_1.png");
		}
		else if(this->getUpgradeLevel() == 1) {
			this->setPower(3);
			this->setRange(Tower::Range::Large);
			this->setRangeShape(_range);
			this->setRateOfFire(Tower::RateOfFire::Fast);
			this->setSellCost(30);
			this->setUpgradeLevel(UpgradeLevel::Upgrade2);
			this->load("resources/images/towers/ShihTzu_2.png");
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