#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <Game.h>
#include "gameObjects/TowerDecorator.h"
#include "gameObjects/FreezeEffect.h"
#include <gameObjects/Tower.h>
#include <gameObjects/ConcreteTower.h>
using std::vector;
using std::map;
using std::cout;
using std::pair;
using std::make_pair;

class TowerManager {
  public:
	static TowerManager& getInstance() {
      static TowerManager instance;   //Guaranteed to be destroyed, instantiated on first use
      return instance;
    }
	TowerManager() {};
	TowerManager(int mapWidth, int mapHeight);
	~TowerManager() {};

	map<pair<int,int>, Tower*>* getTowerMap();
	Tower* getTower(int tileX, int tileY);

	Tower* buyTower(Tower::TowerType type, int tileX, int tileY);
	void sellTower(int tileX, int tileY);

	bool isTileFree(int tileX, int tileY);
	bool outOfBound(int tileX, int tileY) const;

	void clearAllTowers();
	void draw(sf::RenderWindow& gameWindow);

	int tArrayRows;
	int tArrayCols;

	
  private:
	map<pair<int,int>, Tower*> towers;
	 
};