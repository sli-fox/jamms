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

	std::string getTowerSpecs();

};