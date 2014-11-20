#pragma once
#include <GameObjects/Tower.h>

class ConcreteTower : public Tower {

	public:
		static int ConcreteTower::serial;
		static int const ConcreteTower::buy_cost;
		ConcreteTower(int tileX, int tileY);
		int getBuyCost() const;
		void upgradeTower();
		void attack();
		
		std::string getTowerSpecs();

};