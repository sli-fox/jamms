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

	void attack();
	std::string getTowerSpecs();

private:
	std::string _special_effect;

};