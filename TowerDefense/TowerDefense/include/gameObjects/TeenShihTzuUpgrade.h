#pragma once
#include <string>
#include <sstream>
#include <GameObjects/TowerDecorator.h>

class TeenShihTzuUpgrade : public TowerDecorator {
	
	public:
		TeenShihTzuUpgrade();
		TeenShihTzuUpgrade(Tower* decoratedTower);
		~TeenShihTzuUpgrade() { std::cout << red << "TeenShihTzuUpgrade has been deleted." << std::endl; }
		
		static int teen_upgrade_cost;
		
		std::string getTowerSpecs();

	private:
		Tower* _decoratedTower;

};