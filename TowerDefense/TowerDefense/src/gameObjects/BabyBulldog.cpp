#include "GameObjects/BabyBulldog.h"

int const BabyBulldog::buy_cost = 70;

BabyBulldog::BabyBulldog(int tileX, int tileY) {
	this->load("resources/images/towers/Bulldog_0.png");
	this->setPosition(tileX*32, tileY*32);		// has to be set BEFORE setRange();

	this->_id = ConcreteTower::serial++;
	this->_name = "BabyBulldog_" + std::to_string(this->_id);
	this->_type = Tower::TowerType::Bulldog;
	this->_buy_cost = BabyBulldog::buy_cost;
	this->_power = 1;
	this->setRange(1.5);
	this->_rate_of_fire = Tower::RateOfFire::Slow;
	this->_upgrade_cost = 20;
	this->_sell_cost = 30;
	
	std::cout << green << this->_name << " has been created." << std::endl;
}