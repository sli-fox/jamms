#pragma once
#include <GameObjects/Tower.h>

class ShihTzu : public Tower {
	public:
		static int ShihTzu::serial;
		static int const ShihTzu::buy_cost;
		ShihTzu(int tileX, int tileY);
		void upgradeTower();
};