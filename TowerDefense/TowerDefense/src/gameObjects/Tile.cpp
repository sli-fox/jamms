#pragma once
#include "gameObjects/Tile.h"

Tile::Tile(){
	type = EMPTY;
}

Tile::Tile(const string textureID, int tileX, int tileY){
	this->tileX = tileX;
	this->tileY = tileY;
	type = EMPTY;
	file_name = textureID;
	load(file_name);
	sprite.setPosition(float(tileX*32), float(tileY*32));
}

Tile::~Tile(){}

int Tile::getTileX() const{
	return tileX;
}

int Tile::getTileY() const{
	return tileY;
}

Tile::TYPE Tile::getType() const{
	return type;
}

void Tile::setType(Tile::TYPE type){
	this->type = type;
}

PathTile::PathTile(const string textureID, int tileX, int tileY) : Tile(textureID, tileX, tileY){
	setType(Tile::PATH);
}

PathTile::~PathTile(){}

StartTile::StartTile(const string textureID, int tileX, int tileY) : PathTile(textureID, tileX, tileY){
	setType(Tile::START);
}

StartTile::~StartTile(){}

EndTile::EndTile(const string textureID, int tileX, int tileY) : PathTile(textureID, tileX, tileY){
	setType(Tile::END);
}

EndTile::~EndTile(){}

SceneryTile::SceneryTile(const string textureID, int tileX, int tileY) : Tile(textureID, tileX, tileY){
	setType(Tile::SCENERY);
}

SceneryTile::~SceneryTile(){}

DeadTile::DeadTile(const string textureID, int tileX, int tileY) : Tile(textureID, tileX, tileY){
	setType(Tile::DEAD);
}

DeadTile::~DeadTile(){}