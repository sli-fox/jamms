#include "GameObjects/BabyShihTzu.h"

int const BabyShihTzu::buy_cost = 50;

BabyShihTzu::BabyShihTzu(int tileX, int tileY) {
	this->load("resources/images/towers/ShihTzu_0.png");
	this->setPosition(tileX*32, tileY*32);		// has to be set BEFORE setRange();

	this->_id = ConcreteTower::serial++;
	this->_name = "BabyShihTzu_" + std::to_string(this->_id);
	this->_type = Tower::TowerType::ShihTzu;
	this->_buy_cost = BabyShihTzu::buy_cost;
	this->_power = 1;
	this->setRange(1.5);
	this->_rate_of_fire = Tower::RateOfFire::Slow;
	this->_upgrade_cost = 20;
	this->_sell_cost = 30;
	
	std::cout << green << this->_name << " has been created." << std::endl;
}