#pragma once
#include <string>
#include <sstream>
#include <GameObjects/TowerDecorator.h>

class TeenDalmatianUpgrade : public TowerDecorator {
	
	public:
		TeenDalmatianUpgrade();
		TeenDalmatianUpgrade(Tower* decoratedTower);
		~TeenDalmatianUpgrade() { std::cout << red << "TeenDalmatianUpgrade has been deleted." << std::endl; }
		
		static int teen_upgrade_cost;

		void setRange(float _range);
		int getBuyCost() const;
		std::string getTowerSpecs();
		bool canAttack(Critter* critter);
		void attack();

	private:
		Tower* _decoratedTower;

};