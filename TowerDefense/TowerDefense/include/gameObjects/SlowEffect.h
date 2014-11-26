#pragma once
#include <string>
#include <sstream>
#include <GameObjects/TowerDecorator.h>

class SlowEffect : public TowerDecorator {

public:
	SlowEffect();
	SlowEffect(Tower* decoratedTower);
	~SlowEffect() { std::cout << red << "SlowEffect has been deleted." << std::endl; }

	static int upgrade_cost;

	string getTowerSpecs();
	void attack();

private:
	Tower* _decoratedTower;
	string _special_effect;

};