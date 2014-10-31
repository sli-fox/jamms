#pragma once
#include <GameObjects/Tower.h>

class WhiteBloodCellTower : public Tower {
	public:
		static int WhiteBloodCellTower::serial;
		static int const WhiteBloodCellTower::buy_cost;
		WhiteBloodCellTower(sf::Vector2i mousePos);
		void upgradeTower();
};