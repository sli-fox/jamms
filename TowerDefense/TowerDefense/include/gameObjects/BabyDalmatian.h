#pragma once
#include <GameObjects/ConcreteTower.h>

class BabyDalmatian : public ConcreteTower {

public:
	BabyDalmatian() {}
	BabyDalmatian(int tileX, int tileY);
	void upgradeTower();

	static int const BabyDalmatian::buy_cost;

};