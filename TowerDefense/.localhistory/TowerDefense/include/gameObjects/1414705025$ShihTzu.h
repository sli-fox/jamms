#pragma once
#include <GameObjects/Tower.h>

class WhiteBloodCellTower : public Tower {
	public:
		static int WhiteBloodCellTower::serial;
		static int const WhiteBloodCellTower::buy_cost;
		WhiteBloodCellTower(int tileX, int tileY);
		void upgradeTower();
};