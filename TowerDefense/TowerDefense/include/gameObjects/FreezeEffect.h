#pragma once
#include <string>
#include <sstream>
#include <GameObjects/TowerDecorator.h>

class FreezeEffect : public TowerDecorator {
	
	public:
		FreezeEffect();
		FreezeEffect(Tower* decoratedTower);
		~FreezeEffect() { std::cout << red << "FreezeEffect has been deleted." << std::endl; }
		
		static int upgrade_cost;

		void setRange(float _range);
		int getBuyCost() const;
		std::string getTowerSpecs();
		bool canAttack(Critter* critter);
		void attack();

	private:
		Tower* _decoratedTower;
		std::string _special_effect;

};