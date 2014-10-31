#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <Tower.h>
#include <WhiteBloodCellTower.h>
#include <AntibacterialTower.h>
#include <ChemotherapyTower.h>

class TowerManager {
  public:
    TowerManager();
	static void displayTowerArray();
	static Tower* buyTower(Tower::TowerType type, sf::Vector2i mousePos);
	static bool isTileFree(int tileX, int tileY);
	static bool isMouseInMainWindow(sf::Vector2i mousePos);
	static std::vector<std::vector<Tower*> > tArray;

	
  private:
	 
};