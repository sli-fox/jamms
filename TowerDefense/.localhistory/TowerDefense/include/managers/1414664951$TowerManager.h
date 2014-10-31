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
	static void displayTowerArray();
	static Tower* buyTower(Tower::TowerType type, sf::Vector2i mousePos);
	static bool isTileFree(int tileX, int tileY);
	static bool isMouseInMainWindow(sf::Vector2i mousePos);
	static std::vector<std::vector<Tower*> > tArray;

	
  private:
	 
};