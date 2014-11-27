#include "GameObjects/BabyDalmatian.h"

int const BabyDalmatian::buy_cost = 60;

BabyDalmatian::BabyDalmatian(int tileX, int tileY) {
	this->load("resources/images/towers/Dalmatian_0.png");
	this->setPosition(tileX*32, tileY*32);		// has to be set BEFORE setRange();

	this->_id = Tower::serial++;
	this->_name = "Dalmatian_" + std::to_string(this->_id);
	this->_type = Tower::TowerType::Dalmatian;
	this->_buy_cost = BabyDalmatian::buy_cost;
	this->_power = 1;
	this->setRange(1.5);
	this->_rate_of_fire = Tower::RateOfFire::Slow;
	this->_upgrade_cost = 20;
	this->_sell_cost = 30;

	std::cout << green << this->_name << " has been created." << std::endl;
}