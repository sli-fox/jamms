#pragma once
#include "GameObjects/Tower.h"
#include "GameObjects/FreezeEffect.h"

class ConcreteTower : public Tower {

public:
	static int serial;
	static int const upgrade_range_cost;
	ConcreteTower() {}
	void setRange(float _range);
	int getBuyCost() const;
	bool canAttack(Critter* critter);
	void attack();

	std::string getTowerSpecs();

};