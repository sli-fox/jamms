#pragma once
#include <string>
#include <GameObjects/GameObject.h>
#include <GameObjects/Critter.h>
#include <Utils/ConsoleColor.h>
#include <GameObjects/IObserver.h>

class Tower: public GameObject, public IObserver {
  public:
    Tower();
	~Tower() { std::cout << red << _name << " has been deleted." << white << std::endl; };
	virtual void upgradeTower() = 0;
	bool canAttack(Critter* crit);
	void update();

    enum TowerType { ShihTzu, Dalmatian, Bulldog };
	enum UpgradeLevel { Upgrade0, Upgrade1, Upgrade2 };
	enum Range { Small=1, Medium, Large };
	enum RateOfFire { Slow = 1, Normal, Fast };
	enum SpecialEffect { None, Slowing, Burning, Freezing };
	

	//ACCESSORS
    int getID() const;
	std::string getName() const;
    Tower::TowerType getType() const;
	Tower::UpgradeLevel getUpgradeLevel() const;
	int getPower() const;
	Tower::Range getRange() const;
	sf::CircleShape getRangeShape() const;
	Tower::RateOfFire getRateOfFire() const;
	bool getIsFiring() const;
	Tower::SpecialEffect getSpecialEffet() const;
	int getBuyCost() const;
	int getSellCost() const;
	int getUpgradeCost() const;
	Critter* getTarget() const;

	//MUTATORS
    void setID(int _id);
    void setType(Tower::TowerType _tower_type);
	void setUpgradeLevel(Tower::UpgradeLevel _upgrade_level);
	void setPower(int _power);
	void setRange(Tower::Range _range);
	void setRangeShape(Tower::Range range);
	void setRateOfFire(Tower::RateOfFire _rate_of_fire);
	void setIsFiring(bool b);
	void setSpecialEffet(Tower::SpecialEffect _special_effect);
	void setBuyCost(int _buy_cost);
	void setSellCost(int _sell_cost);
	void setUpgradeCost(int _upgrade_cost);
	void setTarget(Critter* crit);

	std::string getTowerSpecs();


  protected:
    int _id;
	std::string _name;
    TowerType _type;
	UpgradeLevel _upgrade_level;
	int _power;
	Range _range;
	sf::CircleShape _range_shape;
	RateOfFire _rate_of_fire;
	SpecialEffect _special_effect;
	int _upgrade_cost;
	int _sell_cost;
	Critter* _target;

  private:
	  sf::Clock clock;
	  sf::Time time;
	
};