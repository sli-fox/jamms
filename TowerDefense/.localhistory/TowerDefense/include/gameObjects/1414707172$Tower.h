#pragma once
#include <string>
#include <GameObjects/GameObject.h>
#include <Utils/ConsoleColor.h>

class Tower: public GameObject {
  public:
    Tower();
	~Tower() { std::cout << red << _name << " has been deleted." << white << std::endl; };
	sf::CircleShape displayRange(int posX, int posY);
	virtual void upgradeTower() = 0;

	// TEMPORARY METHODS TO TEST PLAYER 
	static int getWallet();
	static void updateWallet(int amount);
	// END OF TEMPORARY METHODS

    enum TowerType { ShihTzu, Dalmatian, Bulldog };
	enum UpgradeLevel { Upgrade0, Upgrade1, Upgrade2 };
	enum Range { Small=1, Medium, Large };
	enum RateOfFire { Slow, Normal, Fast };
	enum SpecialEffect { None, Slowing, Burning, Freezing };

	//ACCESSORS
    int getID() const;
	std::string getName() const;
    Tower::TowerType getType() const;
	Tower::UpgradeLevel getUpgradeLevel() const;
	int getPower() const;
	Tower::Range Tower::getRange() const;
	Tower::RateOfFire Tower::getRateOfFire() const;
	Tower::SpecialEffect Tower::getSpecialEffet() const;
	int Tower::getBuyCost() const;
	int Tower::getSellCost() const;
	int Tower::getUpgradeCost() const;
	bool Tower::getInPlayStatus() const;

	//MUTATORS
    void setID(int _id);
    void setType(Tower::TowerType _tower_type);
	void setUpgradeLevel(Tower::UpgradeLevel _upgrade_level);
	void setPower(int _power);
	void Tower::setRange(Tower::Range _range);
	void Tower::setRateOfFire(Tower::RateOfFire _rate_of_fire);
	void Tower::setSpecialEffet(Tower::SpecialEffect _special_effect);
	void Tower::setBuyCost(int _buy_cost);
	void Tower::setSellCost(int _sell_cost);
	void Tower::setUpgradeCost(int _upgrade_cost);
	void Tower::setInPlayStatus(bool _in_play_status);
	
	void Tower::displayTowerSpecs();

  protected:
    int _id;
	std::string _name;
    TowerType _type;
	UpgradeLevel _upgrade_level;
	int _power;
	Range _range;
	RateOfFire _rate_of_fire;
	SpecialEffect _special_effect;
	int _upgrade_cost;
	int _sell_cost;
	bool _is_firing;
	
};