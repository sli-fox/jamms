#pragma once
#include <string>
#include <sstream>
#include <GameObjects/TowerDecorator.h>

class AdultBulldogUpgrade : public TowerDecorator {
	
	public:
		AdultBulldogUpgrade();
		AdultBulldogUpgrade(Tower* decoratedTower);
		~AdultBulldogUpgrade() { std::cout << red << "AdultBulldogUpgrade has been deleted." << std::endl; }
		
		static int adult_upgrade_cost;

		void setRange(float _range);
		int getBuyCost() const;
		std::string getTowerSpecs();
		bool canAttack(Critter* critter);
		void attack();

	private:
		Tower* _decoratedTower;

};