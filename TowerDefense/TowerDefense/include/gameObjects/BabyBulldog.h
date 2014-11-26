#pragma once
#include <GameObjects/Tower.h>

class BabyBulldog : public Tower {

public:
	BabyBulldog() {}
	BabyBulldog(int tileX, int tileY);
	void upgradeTower();

	static int const BabyBulldog::buy_cost;

};