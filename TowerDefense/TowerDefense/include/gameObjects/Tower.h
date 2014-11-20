#pragma once
#include <string>
#include <GameObjects/GameObject.h>
#include <GameObjects/Critter.h>
#include <GameObjects/IObserver.h>
#include "Utils/TowerStrategy.h"
#include <memory>

class Tower: public GameObject, public IObserver{
  public:
    Tower();
	~Tower() { std::cout << red << _name << " has been deleted." << white << std::endl; };
	void upgradeTower() {}
	virtual bool canAttack(Critter* critter) = 0;
	bool canApplySpecialAfterEffects(Critter* critter);
	virtual void attack() = 0;
	void update();
	Critter* executeStrategy(Critter* critter);
	std::pair<float, float> findCollisionPath(Critter* critter);
	void rotateTowardsTarget();
	float angleInDegrees(float x, float y);

    enum TowerType { ShihTzu, Dalmatian, Bulldog };
	enum UpgradeLevel { Upgrade0, Upgrade1, Upgrade2 };
	enum RateOfFire { Slow = 1, Normal, Fast };
	enum SpecialEffect { None, Slowing, Burning, Freezing };
	
	//ACCESSORS
    int getID() const;
	std::string getName() const;
    Tower::TowerType getType() const;
	Tower::UpgradeLevel getUpgradeLevel() const;
	int getPower() const;
	float getRange() const;
	sf::CircleShape getRangeShape() const;
	Tower::RateOfFire getRateOfFire() const;
	bool getIsFiring() const;
	Tower::SpecialEffect getSpecialEffect() const;
	virtual int getBuyCost() const = 0;
	int getSellCost() const;
	int getUpgradeCost() const;
	Critter* getTarget() const;
	TowerStrategy* getStrategy() const;

	//MUTATORS
    void setID(int _id);
	void setName(std::string _name);
    void setType(Tower::TowerType _tower_type);
	void setUpgradeLevel(Tower::UpgradeLevel _upgrade_level);
	void setPower(int _power);
	virtual void setRange(float _range) = 0;
	void setRangeShape(float range);
	void setRateOfFire(Tower::RateOfFire _rate_of_fire);
	void setIsFiring(bool b);
	void setSpecialEffect(Tower::SpecialEffect _special_effect);
	void setBuyCost(int _buy_cost);
	void setSellCost(int _sell_cost);
	void setUpgradeCost(int _upgrade_cost);
	void setTarget(Critter* crit);
	void setStrategy(TowerStrategy* newStrategy);

	virtual std::string getTowerSpecs() = 0;
	virtual bool circleToCircleIntersection(GameObject* game_object);
	void applySpecialEffect(Critter* critter);

  protected:
    int _id;
	std::string _name;
    TowerType _type;
	UpgradeLevel _upgrade_level;
	int _power;
	float _range;
	sf::CircleShape _range_shape;
	RateOfFire _rate_of_fire;
	SpecialEffect _special_effect;
	int _buy_cost;
	int _upgrade_cost;
	int _sell_cost;
	sf::Clock clock;
	sf::Time time;
	Critter* _target;
	std::unique_ptr<TowerStrategy> _strategy;

};