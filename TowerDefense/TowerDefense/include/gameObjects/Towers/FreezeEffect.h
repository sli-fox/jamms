#pragma once
#include <string>
#include <sstream>
#include <GameObjects/Towers/ITower.h>
#include <GameObjects/Towers/ConcreteTower.h>

namespace Dec {

class FreezeEffect : public Dec::ConcreteTower {
	
	public:
		FreezeEffect();
		FreezeEffect(ITower* decoratedTower);
		~FreezeEffect() { std::cout << red << "FreezeEffect has been deleted." << std::endl; }

		std::string getTowerSpecs();
		int getBuyCost() const;
	private:
		ITower* _decoratedTower;
		std::string _effect;

};

}