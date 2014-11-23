#pragma once
#include <GameObjects/Tower.h>

class ConcreteTower : public Tower {

	public:
		static int ConcreteTower::serial;
		static int const ConcreteTower::buy_cost;
		ConcreteTower(int tileX, int tileY);
		void setRange(float _range);
		int getBuyCost() const;
		void upgradeTower();
		bool canAttack(Critter* critter);
		void attack();
		
		std::string getTowerSpecs();

};