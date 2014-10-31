#pragma once
#include <GameObjects/Tower.h>

class Dalmatian : public Tower {
	public:
		static int Dalmatian::id;
		static int const Dalmatian::buy_cost;
		Dalmatian(int tileX, int tileY);
		void upgradeTower();
};