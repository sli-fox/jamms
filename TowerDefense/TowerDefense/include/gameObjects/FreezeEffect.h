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

	string getTowerSpecs();
	void attack();

private:
	string _special_effect;

};