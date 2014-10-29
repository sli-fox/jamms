#pragma once
#include "button.h"
#include "gameObjects\Tile.h"
#include "gameStates\GameStatePlay.h"

class TileSelectButton: public Button{
	Tile::TYPE tileType;
public:
	TileSelectButton(std::string textureName, int posX, int posY, Tile::TYPE tileType);
	virtual ~TileSelectButton();
	void execute(Game* game);
};

class SaveMapButton: public Button{
public:
	SaveMapButton(std::string textureName,int posX, int posY);
	virtual ~SaveMapButton();

	void execute(Game* game);
};

class LoadMapButton: public Button{
public:
	LoadMapButton(std::string textureName,int posX, int posY);
	virtual ~LoadMapButton();

	void execute(Game* game);
};

class CloseEditorButton: public Button{
public:
	CloseEditorButton(std::string textureName,int posX, int posY);
	virtual ~CloseEditorButton();
	
	void execute(Game* game);
};

