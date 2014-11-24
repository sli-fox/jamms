#pragma once
#include <string>
#include <sstream>
#include <GameObjects/TowerDecorator.h>

class AdultShihTzuUpgrade : public TowerDecorator {
	
	public:
		AdultShihTzuUpgrade();
		AdultShihTzuUpgrade(Tower* decoratedTower);
		~AdultShihTzuUpgrade() { std::cout << red << "AdultShihTzuUpgrade has been deleted." << std::endl; }
		
		static int adult_upgrade_cost;

		void setRange(float _range);
		int getBuyCost() const;
		std::string getTowerSpecs();
		bool canAttack(Critter* critter);
		void attack();

	private:
		Tower* _decoratedTower;

};