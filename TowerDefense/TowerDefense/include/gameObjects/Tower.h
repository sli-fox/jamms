#pragma once
#include <string>
#include <GameObjects/TowerGameObject.h>
#include <GameObjects/Critter.h>
#include <utils/TowerStrategy.h>
#include <memory>

class Tower: public TowerGameObject {
public:
	Tower();
	~Tower() { std::cout << red << _name << " has been deleted." << white << std::endl; };

	static int serial;

	void upgradeTower() {}
	bool canApplySpecialAfterEffects(Critter* critter);
	virtual void attack();
	std::pair<float, float> findCollisionPath(Critter* critter);
	void rotateTowardsTarget();
	float angleInDegrees(float x, float y);

	enum TowerType { ShihTzu, Dalmatian, Bulldog };
	enum UpgradeLevel { Baby, Teen, Adult };
	enum SpecialEffect { None, Slowing, Burning, Freezing };

	//ACCESSORS
	int getID() const;
	std::string getName() const;
	Tower::TowerType getType() const;
	Tower::UpgradeLevel getUpgradeLevel() const;
	int getPower() const;
	float getRange() const;
	bool getIsFiring() const;
	Tower::SpecialEffect getSpecialEffect() const;
	int getBuyCost() const;
	int getSellCost() const;
	int getUpgradeCost() const;

	//MUTATORS
	void setID(int _id);
	void setName(std::string _name);
	void setType(Tower::TowerType _tower_type);
	void setUpgradeLevel(Tower::UpgradeLevel _upgrade_level);
	void setPower(int _power);
	void setRange(float _range);
	void setIsFiring(bool b);
	void setSpecialEffect(Tower::SpecialEffect _special_effect);
	void setBuyCost(int _buy_cost);
	void setSellCost(int _sell_cost);
	void setUpgradeCost(int _upgrade_cost);

	virtual string getTowerSpecs();
	void applySpecialEffect(Critter* critter);

protected:
	int _id;
	std::string _name;
	TowerType _type;
	UpgradeLevel _upgrade_level;
	int _power;
	float _range;
	SpecialEffect _special_effect;
	int _buy_cost;
	int _upgrade_cost;
	int _sell_cost;
};