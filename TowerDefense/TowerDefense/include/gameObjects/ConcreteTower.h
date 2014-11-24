#pragma once
#include <GameObjects/Tower.h>

class ConcreteTower : public Tower {

	public:
		static int serial;
		static int const buy_cost;
		static int const upgrade_range_cost;
		ConcreteTower(int tileX, int tileY);
		void setRange(float _range);
		int getBuyCost() const;
		void upgradeTower();
		bool canAttack(Critter* critter);
		void attack();
		
		std::string getTowerSpecs();

};