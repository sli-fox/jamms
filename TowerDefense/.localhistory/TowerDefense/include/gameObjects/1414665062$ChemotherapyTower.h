#pragma once
#include <GameObjects/Tower.h>

class ChemotherapyTower : public Tower {
	public:
		static int ChemotherapyTower::serial;
		static int const ChemotherapyTower::buy_cost;
		ChemotherapyTower(sf::Vector2i mousePos);
		void upgradeTower();
};