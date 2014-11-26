#pragma once
#include <GameObjects/Tower.h>

class BabyShihTzu : public Tower {

public:
	BabyShihTzu() {}
	BabyShihTzu(int tileX, int tileY);
	void upgradeTower();

	static int const BabyShihTzu::buy_cost;

};