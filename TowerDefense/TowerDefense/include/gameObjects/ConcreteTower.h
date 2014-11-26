#pragma once
#include "GameObjects/Tower.h"

class ConcreteTower : public Tower {

public:
	static int ConcreteTower::serial;
	ConcreteTower() {}
	void setRange(float _range);
	int getBuyCost() const;
	bool canAttack(Critter* critter);
	void attack();

	std::string getTowerSpecs();
};