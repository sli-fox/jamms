#pragma once
#include "gameObjects/GameObject.h"
using std::string;

class Tile : public GameObject{
public:
	enum TYPE {PATH, SCENERY, DEAD, START, END, EMPTY};
	
	Tile();
	Tile(const string textureID, int tileX, int tileY);
	virtual ~Tile();

	int getTileX() const;
	int getTileY() const;
	TYPE getType() const;
	
	void setType(TYPE type);

private:
	//member variables
	int tileX, tileY;
	TYPE type;
};

//each tile type is a subclass of tile class (path, scenery, dead)
class PathTile : public Tile{
public:
	PathTile(const string textureID, int tileX, int tileY);
	virtual ~PathTile();
};

//start and end types are a subclass of path class
class StartTile : public PathTile{
public:
	StartTile(const string textureID, int tileX, int tileY);
	virtual ~StartTile();
};

class EndTile : public PathTile{
public:
	EndTile(const string textureID, int tileX, int tileY);
	virtual ~EndTile();
};

class SceneryTile : public Tile{
public:
	SceneryTile(const string textureID, int tileX, int tileY);
	virtual ~SceneryTile();
};

class DeadTile : public Tile{
public:
	DeadTile(const string textureID, int tileX, int tileY);
	virtual ~DeadTile();
};