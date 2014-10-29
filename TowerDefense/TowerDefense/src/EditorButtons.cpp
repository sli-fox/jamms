#include "EditorButtons.h"


TileSelectButton::TileSelectButton(std::string textureName, int posX, int posY, Tile::TYPE tileType) : Button(textureName, posX, posY){
	this->tileType = tileType;
}

TileSelectButton::~TileSelectButton(){

}

void TileSelectButton::execute(Game* game){
	game->tileSelect = tileType;
}

SaveMapButton::SaveMapButton(std::string textureName,int posX, int posY) : Button(textureName, posX, posY){
}

SaveMapButton::~SaveMapButton(){

}

void SaveMapButton::execute(Game* game){
	if(game->map->isMapValid())
		game->saveClicked = true;
}

LoadMapButton::LoadMapButton(std::string textureName, int posX, int posY) : Button(textureName, posX, posY){

}

LoadMapButton::~LoadMapButton(){

}

void LoadMapButton::execute(Game* game){
	game->loadClicked = true;
}

CloseEditorButton::CloseEditorButton(std::string textureName, int posX, int posY) : Button(textureName, posX, posY){

}

CloseEditorButton::~CloseEditorButton(){

}

void CloseEditorButton::execute(Game* game){
	game->pushState(new GameStatePlay(game));
}