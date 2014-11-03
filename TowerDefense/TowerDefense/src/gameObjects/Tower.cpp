#pragma once
#include <GameObjects/Tower.h>

Tower::Tower() {
	this->_upgrade_level = Tower::UpgradeLevel::Upgrade0;
	this->_is_firing = false;
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
void Tower::setIsFiring(bool _is_firing) {
	this->_is_firing = _is_firing;
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
void Tower::attack() {
	std::cout << this->getName() << ": WOUF WOUF!" << std::endl;
}

void Tower::setRangeShape(Tower::Range range) {
	_range_shape.setRadius((range+1) * 32);
	_range_shape.setFillColor(sf::Color::Transparent);
	_range_shape.setOutlineThickness(2);
	_range_shape.setOutlineColor(sf::Color(100, 100, 100));
	_range_shape.setOrigin((this->getRange()*32), (this->getRange()*32));
}

sf::CircleShape Tower::getRangeShape() const {
	return _range_shape;
}

bool Tower::attack(Critter* crit) {
	if(this == NULL) return false;

	int distX = abs(crit->getPosition().x - this->getPosition().x-16);
	int distY = abs(crit->getPosition().y - this->getPosition().y-16);
	int pythagore = static_cast<int> (pow(static_cast<double> (distX), 2))
	+ static_cast<int> (pow(static_cast<double> (distY), 2));

	if(sqrt(pythagore)
	<= this->getRangeShape().getRadius()) {
		_is_firing = true;
		return true;
	}
	return false;
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
sf::Text* Tower::displayWallet() {
	// Declare and load a font
	sf::Font font;
	if(!font.loadFromFile("resources/helveticaneue-webfont.ttf")) {
		std::cout << "FONT NOT LOADED";
	}
	// Create a text
	sf::Text* text = new sf::Text(std::to_string(Tower::getWallet()), font);
	return text;
}
// END OF TEMPORARIES

/*bool Tower::circleToCircleIntersection(GameObject* game_object){
	float radius_1 = this->_range_shape.getRadius();
	float radius_2 = game_object->getRectangleSpriteRadius();

	sf::Vector2f distance = this->getSpriteCenter() - game_object->getSpriteCenter();
	
	return (distance.x * distance.x + distance.y * distance.y) <= (radius_1 + radius_2);
}

void Tower::critterInRange(Critter* critter) {
	if(this->circleToCircleIntersection(critter))
		this->spawnProjectiles();
}*/

void Tower::spawnProjectiles() {

}