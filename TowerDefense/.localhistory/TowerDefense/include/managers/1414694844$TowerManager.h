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
	Tower* getTower(int tileX, int tileY);
	void displayTowerArray();
	Tower* buyTower(Tower::TowerType type, int tileX, int tileY);
	bool isTileFree(int tileX, int tileY);
	bool TowerManager::outOfBound(int tileX, int tileY);
	vector<vector<Tower* const> > tArray;

	//void setArraySize(int tileX, int tileY);
	int tArrayRows;
	int tArrayCols;

	
  private:
	 
};