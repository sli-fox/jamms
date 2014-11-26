#pragma once
#include <string>
#include <GameObjects/TowerGameObject.h>
#include <GameObjects/Critter.h>
#include <GameObjects/IObserver.h>
#include "Utils/TowerStrategy.h"
#include <memory>

class Tower: public TowerGameObject, public IObserver{
public:
  Tower();
  ~Tower() { std::cout << red << _name << " has been deleted." << white << std::endl; };
  void upgradeTower() {}
  virtual bool canAttack(Critter* critter) = 0;
  virtual void attack() = 0;
  void update();
  Critter* executeStrategy(Critter* critter);
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
  void setIsFiring(bool b);
  void setSpecialEffect(Tower::SpecialEffect _special_effect);
  void setBuyCost(int _buy_cost);
  void setSellCost(int _sell_cost);
  void setUpgradeCost(int _upgrade_cost);
  void setTarget(Critter* crit);
  void setStrategy(TowerStrategy* newStrategy);

  virtual std::string getTowerSpecs() = 0;
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
  Critter* _target;
  std::unique_ptr<TowerStrategy> _strategy;

};