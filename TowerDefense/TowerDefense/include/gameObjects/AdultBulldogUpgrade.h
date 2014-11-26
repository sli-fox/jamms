#pragma once
#include <string>
#include <sstream>
#include <GameObjects/TowerDecorator.h>

class AdultBulldogUpgrade : public TowerDecorator {

public:
	AdultBulldogUpgrade();
	AdultBulldogUpgrade(Tower* decoratedTower);
	~AdultBulldogUpgrade() { std::cout << red << "AdultBulldogUpgrade has been deleted." << std::endl; }

	static int adult_upgrade_cost;

	std::string getTowerSpecs();

private:
	Tower* _decoratedTower;

};