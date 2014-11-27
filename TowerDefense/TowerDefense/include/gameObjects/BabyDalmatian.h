#pragma once
#include <GameObjects/Tower.h>

class BabyDalmatian : public Tower {

public:
	BabyDalmatian() {}
	BabyDalmatian(int tileX, int tileY);
	void upgradeTower();

	static int const BabyDalmatian::buy_cost;

};