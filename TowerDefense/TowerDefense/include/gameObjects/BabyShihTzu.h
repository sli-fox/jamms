#pragma once
#include <GameObjects/ConcreteTower.h>

class BabyShihTzu : public ConcreteTower {

public:
	BabyShihTzu() {}
	BabyShihTzu(int tileX, int tileY);
	void upgradeTower();

	static int const BabyShihTzu::buy_cost;

};