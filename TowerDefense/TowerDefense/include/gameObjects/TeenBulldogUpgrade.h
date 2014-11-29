#pragma once
#include <string>
#include <sstream>
#include <GameObjects/TowerDecorator.h>

class TeenBulldogUpgrade : public TowerDecorator {

public:
	TeenBulldogUpgrade();
	TeenBulldogUpgrade(Tower* decoratedTower);
	~TeenBulldogUpgrade() { std::cout << red << "TeenBulldogUpgrade has been deleted." << std::endl; }

	static int teen_upgrade_cost;

	std::string getTowerSpecs();

};