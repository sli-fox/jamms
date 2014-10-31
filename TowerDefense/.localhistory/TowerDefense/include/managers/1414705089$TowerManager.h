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
	static TowerManager& getInstance() {
      static TowerManager instance;   //Guaranteed to be destroyed, instantiated on first use
      return instance;
    }
	TowerManager();
    //TowerManager(int mapWidth, int mapHeight);
	~TowerManager() {};
	Tower* getTower(int tileX, int tileY);
	void displayTowerArray();
	Tower* buyTower(Tower::TowerType type, int tileX, int tileY);
	void sellTower(int tileX, int tileY);
	bool isTileFree(int tileX, int tileY);
	bool TowerManager::outOfBound(int tileX, int tileY);

	void setArraySize(int mapWidth, int mapHeight);
	void draw(sf::RenderWindow& gameWindow);

	int tArrayRows;
	int tArrayCols;

	
  private:
	 vector<vector<Tower*> > tArray;
	 
};