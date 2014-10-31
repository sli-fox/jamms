#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <gameObjects/Tower.h>
#include <gameObjects/WhiteBloodCellTower.h>
#include <gameObjects/AntibacterialTower.h>
#include <gameObjects/ChemotherapyTower.h>
using std::vector;
using std::cout;

class TowerManager {
  public:
	TowerManager();
    TowerManager(int mapWidth, int mapHeight);
	vector<vector<Tower*> > gettArray();
	Tower* getTower(int tileX, int tileY);
	void displayTowerArray();
	Tower* buyTower(Tower::TowerType type, int tileX, int tileY);
	bool isTileFree(int tileX, int tileY);
	bool isMouseInMainWindow(sf::Vector2i mousePos);
	std::vector<std::vector<Tower*> > tArray;
	int tArrayRows;
	int tArrayCols;

	
  private:
	 
};