#pragma once
#include <GameObjects/Tower.h>

class Bulldog : public Tower {
	public:
		static int Bulldog::serial;
		static int const Bulldog::buy_cost;
		Bulldog(int tileX, int tileY);
		void upgradeTower();
};