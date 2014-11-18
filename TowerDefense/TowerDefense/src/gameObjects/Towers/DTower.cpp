#pragma once
#include <GameObjects/Towers/DTower.h>

int DTower::serial = 0;		// used to increment _id

DTower::DTower() {
	std::cout << green << "DTower Default Constructor Called." << std::endl;
}

DTower::DTower(int tileX, int tileY) {
	this->D_id = DTower::serial++;
	this->D_tileX = tileX;
	this->D_tileY = tileY;
	this->load("resources/images/towers/tower.png");
	this->setPosition(tileX*32, tileY*32);
	std::cout << green << "DTower #" << this->D_id << " has been created." << std::endl;
}

// ACCESSORS
int DTower::DgetID() const {
	return D_id;
}
int DTower::DgetBuyCost() const {
	return D_buy_cost;
}
int DTower::DgetSellCost() const {
	return D_sell_cost;
}
// MUTATORS
void DTower::DsetSellCost(int _sell_cost) {
	this->D_sell_cost = _sell_cost;
}

std::string DTower::DgetTowerSpecs() {
	std::stringstream output;
	output << "CURRENT TOWER SPECIFICATIONS:" << std::endl;
	output << "ID: " << this->D_id << std::endl;
	output << "Buy Cost: " << this->D_buy_cost << " coins" << std::endl;
	output << "Sell Cost: " << this->D_sell_cost << " coins" << std::endl;

	return output.str();
}