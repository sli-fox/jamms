#pragma once
#include <string>
#include <sstream>
#include <GameObjects/TowerDecorator.h>

class AdultDalmatianUpgrade : public TowerDecorator {
	
	public:
		AdultDalmatianUpgrade();
		AdultDalmatianUpgrade(Tower* decoratedTower);
		~AdultDalmatianUpgrade() { std::cout << red << "AdultDalmatianUpgrade has been deleted." << std::endl; }
		
		static int adult_upgrade_cost;

		void setRange(float _range);
		int getBuyCost() const;
		std::string getTowerSpecs();
		bool canAttack(Critter* critter);
		void attack();

	private:
		Tower* _decoratedTower;

};