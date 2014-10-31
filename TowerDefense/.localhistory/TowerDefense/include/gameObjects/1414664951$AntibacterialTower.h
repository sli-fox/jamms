#pragma once
#include <GameObjects/Tower.h>

class AntibacterialTower : public Tower {
	public:
		static int AntibacterialTower::serial;
		static int const AntibacterialTower::buy_cost;
		AntibacterialTower(sf::Vector2i mousePos);
		void upgradeTower();
};