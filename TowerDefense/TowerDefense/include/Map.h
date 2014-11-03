#pragma once
#include <vector>
#include <deque>
#include <fstream>
#include <string>
#include <iostream>
#include <memory>
#include "gameObjects/Tile.h"
#include "utils/rapidxml.hpp"
#include "utils/rapidxml_print.hpp"
#include <sstream>
#include <stack>
using std::vector;
using std::deque;
using std::unique_ptr;
using std::bad_exception;
using std::ostringstream;
using std::stack;
using std::cin;
using std::cout;
using std::endl;

class Map{
private:
	//A 2D vector of unique Tile pointers
	vector<vector<unique_ptr<Tile>>> tileMap;
	//A double ended queue of const Tile pointers
	deque<const Tile* const> mapPath;
	//A 2D vector of unique GameObjects (for tower/critter placement testing purposes)
	vector<vector<unique_ptr<GameObject>>> mapObjects;

	//map attributes
	int mapWidth, mapHeight;
	bool hasStart, hasEnd;
	string imagePath;

	//returns true  if tile/object placement is outside map boundaries
	bool outOfBounds(const int tileX, const int tileY) const;
	//validates user path placement
	bool validPathPlacement(const int tileX, const int tileY);
	//conversion of strings to enum for tiletypes (type safety purposes)
	Tile::TYPE convertType(const string tileTypeString) const;
	string convertType(Tile::TYPE type) const;

public:
	static const int MAX_MAP_WIDTH = 32;
	static const int MAX_MAP_HEIGHT = 12;

	//loads map from filename
	Map(string mapName);
	//creates blank map of initial size specified by the user
	Map(int mapWidth, int mapHeight);
	virtual ~Map();

	int getMapWidth() const;
	int getMapHeight() const;
	
	//resizes 2D vector of array tiles according to parameters
	void setMapSize(const int mapWidth, const int mapHeight);

	//returns a constant tile pointer to the tile at position passed as a parameter. Throws std::bad_exception if OutOfBounds returns true
	//WARNING: Do not delete any pointer to a tile or program will crash
	//WARNING: Could return nullptr if out of map bounds
	const Tile* const getTile(const int tileX, const int tileY) const;

	//adds a tile with passed textureID, texturetype (as a string), and position
	void addTile(int tileX, int tileY, const Tile::TYPE tileType);

	//removes a tile at passed position
	void removeTile(const int tileX, const int tileY);
	
	//returns a copy of double ended queue with constant Tile pointers (used by outside modules to get read-only position of path tiles)
	//from start to finish, each succesive pop_front() of the queue returns a constant pointer to the next tile in the map path
	//WARNING: Do not delete any pointer to a tile or program will crash
	deque<const Tile* const> getMapPath() const;

	//returns true if map contains a connected start and end tile
	bool isMapValid();

	//fills map with Empty tiles
	void blankMap();

	//clears and resizes tileMap and mapObjects containers to 0
	void resetMap();

	//fills empty tiles with scenery tiles upon map validation (to simplify creation process)
	void fillMap();

	//loads Map from filename
	void load(const string filename);

	//saves Map to filename
	void save(const string filename);

	//draws map to game window specified as parameter
	void draw(sf::RenderWindow& gameWindow);

	//collection of get, place, and remove functions for critter and tower objects (testing purposes)
	//WARNING: Could return nullptr if out of map bounds
	const GameObject* const getGameObject(const int tileX, const int tileY);
	void removeGameObject(const int tileX, const int tileY);
	void placeCritter(const string critterName, const int tileX, const int tileY);
	void placeTower(const string towerName, const int tileX, const int tileY);
};