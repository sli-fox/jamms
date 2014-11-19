#pragma once
#include <GameObjects/Towers/ConcreteTower.h>

int Dec::ConcreteTower::serial = 0;		// used to increment _id

Dec::ConcreteTower::ConcreteTower() {
	std::cout << green << "DTower Default Constructor Called." << std::endl;
}

Dec::ConcreteTower::ConcreteTower(int tileX, int tileY) {
	this->_id = Dec::ConcreteTower::serial++;
	this->_tileX = tileX;
	this->_tileY = tileY;
	this->_buy_cost = 50;
	this->_sell_cost = 20;
	this->load("resources/images/towers/tower.png");
	this->setPosition(tileX*32, tileY*32);
}

// ACCESSORS
int Dec::ConcreteTower::getID() const {
	return _id;
}
int Dec::ConcreteTower::getBuyCost() const {
	return _buy_cost;
}
int Dec::ConcreteTower::getSellCost() const {
	return _sell_cost;
}
// MUTATORS
void Dec::ConcreteTower::setBuyCost(int _buy_cost) {
	this->_buy_cost = _buy_cost;
}
void Dec::ConcreteTower::setSellCost(int _sell_cost) {
	this->_sell_cost = _sell_cost;
}

void Dec::ConcreteTower::attack() {
	std::cout << yellow << "Attacking..." << std::endl;
}

// @Override
std::string Dec::ConcreteTower::getTowerSpecs() {
	std::stringstream output;
	output << "ID: " << this->_id << std::endl;
	output << "Buy Cost: " << this->_buy_cost << " coins" << std::endl;
	output << "Sell Cost: " << this->_sell_cost << " coins" << std::endl;
	std::cout << blue << output.str() << std::endl;
	return output.str();
}