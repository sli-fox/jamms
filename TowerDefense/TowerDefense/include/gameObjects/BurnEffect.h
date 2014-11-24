#pragma once
#include <string>
#include <sstream>
#include <GameObjects/TowerDecorator.h>

class BurnEffect : public TowerDecorator {
	
	public:
		BurnEffect();
		BurnEffect(Tower* decoratedTower);
		~BurnEffect() { std::cout << red << "BurnEffect has been deleted." << std::endl; }

		static int upgrade_cost;

		int getBuyCost() const;
		void setRange(float _range);
		std::string getTowerSpecs();
		bool canAttack(Critter* critter);
		void attack();

	private:
		Tower* _decoratedTower;
		std::string _special_effect;

};