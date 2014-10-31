#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <GameObjects/Tower.h>
#include <GameObjects/WhiteBloodCellTower.h>
#include <GameObjects/AntibacterialTower.h>
#include <GameObjects/ChemotherapyTower.h>

class TowerManager {
  public:
	TowerManager() {}
    TowerManager(int mapWidth, int mapHeight);
	void displayTowerArray();
	Tower* buyTower(Tower::TowerType type, int tileX, int tileY);
	bool isTileFree(int tileX, int tileY);
	bool isMouseInMainWindow(sf::Vector2i mousePos);
	std::vector<std::vector<Tower*> > tArray;

	
  private:
	  int tArrayRows;
	  int tArrayCols;
	 
};