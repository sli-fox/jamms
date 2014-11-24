#pragma once
#include <GameObjects/ConcreteTower.h>

class BabyBulldog : public ConcreteTower {

public:
	BabyBulldog() {}
	BabyBulldog(int tileX, int tileY);
	void upgradeTower();

	static int const BabyBulldog::buy_cost;

};