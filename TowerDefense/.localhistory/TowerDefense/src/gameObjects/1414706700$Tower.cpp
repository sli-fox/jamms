#pragma once
#include <GameObjects/Tower.h>

Tower::Tower() {
	this->_upgrade_level = Tower::UpgradeLevel::Upgrade0;
}

//ACCESSORS
int Tower::getID() const {
	return _id;
}
std::string Tower::getName() const {
	return _name;
}
Tower::TowerType Tower::getType() const {
	return _type;
}
Tower::UpgradeLevel Tower::getUpgradeLevel() const {
	return _upgrade_level;
}
int Tower::getPower() const {
	return _power;
}
Tower::Range Tower::getRange() const {
	return _range;
}
Tower::RateOfFire Tower::getRateOfFire() const {
	return _rate_of_fire;
}
Tower::SpecialEffect Tower::getSpecialEffet() const {
	return _special_effect;
}
int Tower::getSellCost() const {
	return _sell_cost;
}
int Tower::getUpgradeCost() const {
	return _upgrade_cost;
}
bool Tower::getInPlayStatus() const {
	return _is_firing;
}

//MUTATORS
void Tower::setID(int _id) {
	this->_id = _id;
}
void Tower::setType(Tower::TowerType _tower_type) {
	this->_type = _tower_type;
}
void Tower::setUpgradeLevel(Tower::UpgradeLevel _upgrade_level) {
	this->_upgrade_level = _upgrade_level;
}
void Tower::setPower(int _power) {
	this->_power = _power;
}
void Tower::setRange(Tower::Range _range) {
	this->_range = _range;
}
void Tower::setRateOfFire(Tower::RateOfFire _rate_of_fire) {
	this->_rate_of_fire = _rate_of_fire;
}
void Tower::setSpecialEffet(Tower::SpecialEffect _special_effect) {
	this->_special_effect = _special_effect;
}
void Tower::setSellCost(int _sell_cost) {
	this->_sell_cost = _sell_cost;
}
void Tower::setUpgradeCost(int _upgrade_cost) {
	this->_upgrade_cost = _upgrade_cost;
}
void Tower::setInPlayStatus(bool _in_play_status) {
	this->_in_play_status = _in_play_status;
}

sf::CircleShape Tower::displayRange(int posX, int posY) {
	sf::CircleShape range((this->getRange()+1) * 32);
	range.setFillColor(sf::Color::Transparent);
	range.setOutlineThickness(2);
	range.setOutlineColor(sf::Color(100, 100, 100));
	range.setOrigin((this->getRange()*32), (this->getRange()*32));
	range.setPosition(posX-16, posY-16);
	return range;
}

void Tower::displayTowerSpecs() {
	//Since we can't cout an enum in C++, we need this Array system as a workaround (optional, but prettier at output)
	char *TowerTypeA[] = { "WhiteBloodCellTower", "AntibacterialTower", "ChemotherapyTower" };
	char *UpgradeLevelA[] = { "Upgrade0", "Upgrade1", "Upgrade2" };
	char *RangeA[] = { "Small", "Medium", "Large" };
	char *RateOfFireA[] = { "Slow", "Normal", "Fast" };
	char *SpecialEffectA[] = { "None", "Slowing", "Burning", "Freezing" };
	char *BooleanA[] = { "False", "True" };
	
				// Changing console color to Blue, because.
	std::cout	<< blue << "TOWER SPECIFICATIONS:" << std::endl
				<< "-------------------------------------------------------" << std::endl
				<< "Name: \t\t" << this->_name << std::endl
				<< "Type: \t\t" << TowerTypeA[this->_type] << std::endl
				<< "Upgrade: \t" << UpgradeLevelA[this->_upgrade_level] << std::endl
				<< "Power: \t\t" << this->_power << std::endl
				<< "Range: \t\t" << RangeA[this->_range-1] << std::endl
				<< "Fire Rate: \t" << RateOfFireA[this->_rate_of_fire] << std::endl
				<< "Special Effect: " << SpecialEffectA[this->_special_effect] << std::endl
				<< "Upgrade Cost: \t" << this->_upgrade_cost << std::endl
				<< "Sell Cost: \t" << this->_sell_cost << std::endl
				<< "-------------------------------------------------------" << std::endl << std::endl;
}

// TEMPORARY WALLET ATTRIBUTE FOR TESTING TOWERS' COST
static int wallet = 5000;		// player money
int Tower::getWallet() {
	return wallet;
}
void Tower::updateWallet(int amount) {
	wallet += amount;
}