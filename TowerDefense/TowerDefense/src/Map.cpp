#pragma once
#include "Map.h"

Map::Map(string mapName){
	imagePath = "resources/images/";
	load(mapName);
}

Map::Map(int mapWidth, int mapHeight){
	imagePath = "resources/images/";
	hasStart = false;
	hasEnd = false;
	setMapSize(mapWidth, mapHeight);
	blankMap();
}

Map::~Map(){

}

int Map::getMapWidth() const{
	return mapWidth;
}

int Map::getMapHeight() const{
	return mapHeight;
}

const Tile* const Map::getTile(const int tileX, const int tileY) const{
	if(!outOfBounds(tileX, tileY))
		return tileMap[tileX][tileY].get();
	else
		return nullptr;
}

deque<const Tile* const> Map::getMapPath() const{
	return mapPath;
}

void Map::setMapSize(const int mapWidth, const int mapHeight){
	if(mapWidth <= MAX_MAP_WIDTH && mapHeight <= MAX_MAP_HEIGHT){
		this->mapWidth = mapWidth;
		this->mapHeight = mapHeight;

		//resize 1st dimension of vector to mapWidth (number of tiles width-wise)
		tileMap.resize(mapWidth);
		mapObjects.resize(mapWidth);

		//resize 2nd dimension of vector to mapHeight(number of tiles height-wise)
		for(int i = 0; i < mapWidth; ++i)
		{
			tileMap.at(i).resize(mapHeight);
			mapObjects.at(i).resize(mapHeight);
		}
	}
	else
		cout << "Invalid map size! Max size is: " << MAX_MAP_WIDTH << ", " << MAX_MAP_HEIGHT << endl;
}

void Map::resetMap(){
	hasStart = false;
	hasEnd = false;
	mapPath.clear();
	mapObjects.clear();
	mapObjects.shrink_to_fit();
	tileMap.clear();
	tileMap.shrink_to_fit();
}

void Map::blankMap(){
	for(int tileX = 0; tileX < mapWidth; ++tileX){
		for(int tileY = 0 ; tileY < mapHeight; ++tileY){
			if(tileMap[tileX][tileY] == nullptr)
				tileMap[tileX][tileY].reset(new Tile(imagePath + "blank.png", tileX, tileY));	
			else
				removeTile(tileX, tileY);
		}
	}
}

void Map::fillMap(){
for(int tileX = 0 ; tileX < mapWidth ; ++tileX){
		for(int tileY = 0 ; tileY < mapHeight ; ++tileY){
			if(tileMap[tileX][tileY]->getType() == Tile::EMPTY)
				tileMap[tileX][tileY].reset(new SceneryTile(imagePath + "scenery.png", tileX, tileY));
		}
	}
}

void Map::unfillMap(){
for(int tileX = 0 ; tileX < mapWidth ; ++tileX){
		for(int tileY = 0 ; tileY < mapHeight ; ++tileY){
			if(tileMap[tileX][tileY]->getType() == Tile::SCENERY)
				tileMap[tileX][tileY].reset(new Tile(imagePath + "blank.png", tileX, tileY));	
		}
	}
}

bool Map::isMapValid(){
	bool hasEmpty = false;
	for(int i = 0 ; i < mapWidth ; ++i){
		for(int j = 0 ; j < mapHeight ; ++j){
			if(tileMap[i][j]->getType() == Tile::EMPTY){
				hasEmpty = true;
				break;
			}
		}
	}

	if(!hasStart){
		cout << "missing Start tile!" << endl;
	}
	if(!hasEnd){
		cout << "missing End tile!" << endl;
	}
	if(hasEmpty){
		cout << "map still has Empty tiles!" << endl;
	}
	return hasStart && hasEnd && !hasEmpty;
}

//checks adjacent tiles to path to be placed, returns true if it is a valid placement
bool Map::validPathPlacement(const int tileX, const int tileY){
	int adjacentTileCtr = 0;
	bool isNextTile = false;
	
	if(!outOfBounds(tileX+1, tileY) && (tileMap[tileX+1][tileY]->getType() == Tile::PATH || tileMap[tileX+1][tileY]->getType() == Tile::START)){
		if(mapPath.back()->getTileX() == tileX+1 && mapPath.back()->getTileY() == tileY)
			isNextTile = true;
		++adjacentTileCtr;
	}
	if(!outOfBounds(tileX, tileY+1) && (tileMap[tileX][tileY+1]->getType() == Tile::PATH || tileMap[tileX][tileY+1]->getType() == Tile::START)){
		if(mapPath.back()->getTileX() == tileX && mapPath.back()->getTileY() == tileY+1)
			isNextTile = true;
		++adjacentTileCtr;
	}
	if(!outOfBounds(tileX-1, tileY) && (tileMap[tileX-1][tileY]->getType() == Tile::PATH || tileMap[tileX-1][tileY]->getType() == Tile::START)){
		if(mapPath.back()->getTileX() == tileX-1 && mapPath.back()->getTileY() == tileY)
			isNextTile = true;
		++adjacentTileCtr;
	}
	if(!outOfBounds(tileX, tileY-1) && (tileMap[tileX][tileY-1]->getType() == Tile::PATH || tileMap[tileX][tileY-1]->getType() == Tile::START)){
		if(mapPath.back()->getTileX() == tileX && mapPath.back()->getTileY() == tileY-1)
			isNextTile = true;
		++adjacentTileCtr;
	}
	return adjacentTileCtr < 2 && isNextTile;
}

//returns true if position is outside of map boundaries
bool Map::outOfBounds(const int tileX, const int tileY) const{
	return (!(-1 < tileX && tileX < mapWidth) || !(-1 < tileY && tileY < mapHeight));
}

//private conversion function
Tile::TYPE Map::convertType(const string tileTypeString) const{
	if(tileTypeString == "start")
		return Tile::START;
	else if(tileTypeString == "end")
		return Tile::END;
	else if(tileTypeString == "path")
		return Tile::PATH;
	else if(tileTypeString == "scenery")
		return Tile::SCENERY;
	else if(tileTypeString == "dead")
		return Tile::DEAD;
	else
		return Tile::EMPTY;
}

//private conversion function
string Map::convertType(Tile::TYPE type) const{
	if(type == Tile::START)
		return "start";
	else if(type == Tile::END)
		return "end";
	else if(type == Tile::PATH)
		return "path";
	else if(type == Tile::SCENERY)
		return "scenery";
	else if(type == Tile::DEAD)
		return "dead";
	else
		return "empty";
}

//creates tile and adds it according to its type. If path, start, or end; adds tile to mapPath queue accordingly
bool Map::addTile(int tileX, int tileY, const Tile::TYPE tileType){
	if(!outOfBounds(tileX, tileY) && getTile(tileX, tileY)->getType() != Tile::EMPTY){
		cout << "Tile not empty" << endl;
		return false;
	}
	if(!outOfBounds(tileX, tileY)){
		switch(tileType){
		case(Tile::START):{
				if(hasEnd){
					cout << "Remove end tile first" << endl;
					return false;
				}
				else if(hasStart){
					cout << "Start tile already exists" << endl;
					return false;
				}
					tileMap[tileX][tileY].reset(new StartTile(imagePath + "start.png", tileX, tileY));
					mapPath.push_back(getTile(tileX, tileY));
					hasStart = true;
					break;
						  }
		case(Tile::END):{
			if(hasEnd){
				cout << "Remove end tile first" << endl;
					return false;
			}
			else if(!hasStart){
				cout << "Place a start tile first" << endl;
					return false;
			}

			if(validPathPlacement(tileX, tileY)){
				tileMap[tileX][tileY].reset(new EndTile(imagePath + "end.png", tileX, tileY));
				mapPath.push_back(getTile(tileX, tileY));
				hasEnd = true;
			}
			else
			{
				cout << "Not a valid end placement" << endl;
				return false;
			}
			break;
						}
		case(Tile::PATH):{
			if(hasEnd){
				cout << "Remove end tile first" << endl;
					return false;
			}
			else if(!hasStart){
				cout << "Place a start tile first" << endl;
				return false;
			}

			if(validPathPlacement(tileX, tileY)){
				tileMap[tileX][tileY].reset(new PathTile(imagePath + "path.png", tileX, tileY));
				mapPath.push_back(getTile(tileX, tileY));
			}
			else
			{
				cout << "Not a valid path placement" << endl;
				return false;
			}
			break;
						 }
		case(Tile::DEAD):{
			tileMap[tileX][tileY].reset(new DeadTile(imagePath + "dead.png", tileX, tileY));
			break;
						 }
		case(Tile::SCENERY):{
			tileMap[tileX][tileY].reset(new SceneryTile(imagePath + "scenery.png", tileX, tileY));
			break;
							}
		default:{
			cout << "No tile could be placed" << endl;
			return false;
			break;
				}
		}
	}

	return true;
}

//removes tile at position specified, and if it is in the mapPath queue, removes it.
//if removing a path tile would invalidate the map path, all tiles in the queue that appear after removed tile
//are deleted from the queue and the map
void Map::removeTile(const int tileX, const int tileY){
	if(!outOfBounds(tileX, tileY) && getTile(tileX, tileY)->getType() == Tile::EMPTY)
		return;
	if(!outOfBounds(tileX, tileY) && getTile(tileX, tileY)->getType() == Tile::START){
		while(!mapPath.empty()){
			int thisX = mapPath.back()->getTileX();
			int thisY = mapPath.back()->getTileY();
			mapPath.pop_back();
			tileMap[thisX][thisY].reset(new Tile(imagePath + "blank.png", thisX, thisY));
			removeGameObject(thisX, thisY);
		}
		mapPath.shrink_to_fit();
		hasStart = false;
		hasEnd = false;
		return;
	}
	if(!outOfBounds(tileX, tileY) && getTile(tileX, tileY)->getType() == Tile::END){
		int thisX = mapPath.back()->getTileX();
		int thisY = mapPath.back()->getTileY();
		mapPath.pop_back();
		tileMap[thisX][thisY].reset(new Tile(imagePath + "blank.png", thisX, thisY));
		removeGameObject(thisX, thisY);
		mapPath.shrink_to_fit();
		hasEnd = false;
		return;
	}
	if(!outOfBounds(tileX, tileY) && getTile(tileX, tileY)->getType() == Tile::PATH){
		while(!(mapPath.back()->getTileX() == tileX && mapPath.back()->getTileY() == tileY)){
			int thisX = mapPath.back()->getTileX();
			int thisY = mapPath.back()->getTileY();
			if(getTile(thisX,thisY)->getType() == Tile::END)
				hasEnd = false;
			mapPath.pop_back();
			tileMap[thisX][thisY].reset(new Tile(imagePath + "blank.png", thisX, thisY));
			removeGameObject(thisX, thisY);
		}
		mapPath.shrink_to_fit();
		if(mapPath.back()->getTileX() == tileX && mapPath.back()->getTileY() == tileY){
			int thisX = mapPath.back()->getTileX();
			int thisY = mapPath.back()->getTileY();
			mapPath.pop_back();
			tileMap[thisX][thisY].reset(new Tile(imagePath + "blank.png", thisX, thisY));
			removeGameObject(thisX, thisY);
			mapPath.shrink_to_fit();
			return;
		}
	}
	if(!outOfBounds(tileX, tileY) && (getTile(tileX, tileY)->getType() == Tile::SCENERY || getTile(tileX, tileY)->getType() == Tile::DEAD)){
		tileMap[tileX][tileY].reset(new Tile(imagePath + "blank.png", tileX, tileY));
		removeGameObject(tileX, tileY);
	}
}

void Map::save(const string filename){
	using namespace rapidxml;
	if(!isMapValid()){
		cout << "Map not valid, can't be saved" << endl;
		return;
	}
	xml_document<> xmlDoc;
	ostringstream os;
	stack<string> store;
	const char* value;
	os << mapWidth;
	store.push(os.str());
	value = store.top().c_str();

	xml_node<>* root = xmlDoc.allocate_node(node_element, "map");
	root->append_attribute(xmlDoc.allocate_attribute("width", value));
	os.str(string());
	os << mapHeight;
	store.push(os.str());
	value = store.top().c_str();
	root->append_attribute(xmlDoc.allocate_attribute("height", value));
	os.str(string());
	xmlDoc.append_node(root);

	deque<const Tile* const> path = getMapPath();
	xml_node<>* pathTile;
	while(!path.empty()){
	 pathTile = xmlDoc.allocate_node(node_element, "pathTile");
	 int x = path.front()->getTileX();
	 int y = path.front()->getTileY();
	 string tileType = convertType(path.front()->getType());
	 string textureID = path.front()->getFileName();
	 path.pop_front();

	 os << x;
	 store.push(os.str());
	 value = store.top().c_str();
	 pathTile->append_attribute(xmlDoc.allocate_attribute("x", value));
	 os.str(string());
	 os << y;
	 store.push(os.str());
	 value = store.top().c_str();
	 pathTile->append_attribute(xmlDoc.allocate_attribute("y", value));
	 os.str(string());
	 os << tileType;
	 store.push(os.str());
	 value = store.top().c_str();
	 pathTile->append_attribute(xmlDoc.allocate_attribute("tileType", value));
	 os.str(string());
	 os << textureID;
	 store.push(os.str());
	 value = store.top().c_str();
	 pathTile->append_attribute(xmlDoc.allocate_attribute("textureID", value));
	 os.str(string());
	 root->append_node(pathTile);
	}
	xml_node<>* tile;
	for(int tileX = 0; tileX < mapWidth ; ++tileX){
		for(int tileY = 0; tileY < mapHeight ; ++tileY){
			if(tileMap[tileX][tileY]->getType() == Tile::SCENERY ||
				tileMap[tileX][tileY]->getType() == Tile::DEAD){
				tile = xmlDoc.allocate_node(node_element, "tile");
				string tileType = convertType(tileMap[tileX][tileY]->getType());
				string textureID = tileMap[tileX][tileY]->getFileName();

				 os << tileX;
				 store.push(os.str());
	             value = store.top().c_str();
				 tile->append_attribute(xmlDoc.allocate_attribute("x", value));
				 os.str(string());
				 os << tileY;
				 store.push(os.str());
	             value = store.top().c_str();
				 tile->append_attribute(xmlDoc.allocate_attribute("y", value));
				 os.str(string());
				 os << tileType;
				 store.push(os.str());
	             value = store.top().c_str();
				 tile->append_attribute(xmlDoc.allocate_attribute("tileType", value));
				 os.str(string());
				 os << textureID;
				 store.push(os.str());
	             value = store.top().c_str();
				 tile->append_attribute(xmlDoc.allocate_attribute("textureID", value));
				 os.str(string());
				 root->append_node(tile);
			}
		}
	}
	value = nullptr;
	os.clear();
	std::ofstream thisMap;
	if(int(filename.size()) > 0)
		thisMap.open("resources/maps/" + filename + ".xml", std::ofstream::out | std::ofstream::trunc);
	if(!thisMap.is_open()){
		xmlDoc.clear();
		cout << "Map could not be saved" << endl;
		return;
	}
	thisMap << xmlDoc;
	thisMap.close();
	xmlDoc.clear();
	cout << "Saved successfully" << endl;
}

void Map::load(string filename){
	using namespace rapidxml;
	std::ifstream inFile;
	inFile.open("resources/maps/" + filename);
	if(!inFile.is_open())
		return;

	//Dump contents of file into a string
	string xmlString;
	string line;

	while(getline(inFile,line))
		xmlString +=line;

	inFile.close();

	//Convert string to rapidxml readable char*
	vector<char> xmlData = vector<char>(xmlString.begin(), xmlString.end());
	xmlData.push_back('\0');

	//Create a parsed document with &xmlData[0] which is the char*
	xml_document<> xmlLoad;
	xmlLoad.parse<parse_no_data_nodes>(&xmlData[0]);

	//Get the root node
	xml_node<>* root = xmlLoad.first_node();

	//Get map attributes
	int mapW = atoi(root->first_attribute("width")->value());
	int mapH = atoi(root->first_attribute("height")->value());
	
	//Reset and initialize blank map
	resetMap();
	setMapSize(mapW, mapH);
	blankMap();

	//Go through each tile
	xml_node<>* tile = root->first_node();
	while(tile)
	{
		//Get all the attributes
		int tileX = atoi(tile->first_attribute("x")->value());
		int tileY = atoi(tile->first_attribute("y")->value());
		string tileTypeString = tile->first_attribute("tileType")->value();
		string textureID = tile->first_attribute("textureID")->value();

		Tile::TYPE tileType = convertType(tileTypeString);

		addTile(tileX, tileY, tileType);

		tile = tile->next_sibling();
	}
	xmlLoad.clear();
	cout << "Map loaded successfully" << endl;
}

//implementations for game objects similar to implementation for tile objects
const GameObject* const Map::getGameObject(const int tileX, const int tileY){
	if(!outOfBounds(tileX, tileY))
		return mapObjects[tileX][tileY].get();
	else
		return nullptr;
}

void Map::removeGameObject(const int tileX, const int tileY){
	if(!outOfBounds(tileX, tileY) && mapObjects[tileX][tileY] != nullptr)
		mapObjects[tileX][tileY].reset(nullptr);
}

void Map::placeCritter(const string textureID, const int tileX, int const tileY){
	if(!outOfBounds(tileX, tileY) && (getTile(tileX, tileY)->getType() == Tile::PATH || getTile(tileX, tileY)->getType() == Tile::START || getTile(tileX, tileY)->getType() == Tile::END)){
		mapObjects[tileX][tileY].reset(new GameObject());
		mapObjects[tileX][tileY]->load(textureID);
		mapObjects[tileX][tileY]->setPosition(float(tileX*32), float(tileY*32));
	}
	else
		cout << "Critter not placed" << endl;
}
void Map::placeTower(const string textureID, const int tileX, const int tileY){
	if(!outOfBounds(tileX, tileY) && (getTile(tileX, tileY)->getType() == Tile::SCENERY)){
		mapObjects[tileX][tileY].reset(new GameObject());
		mapObjects[tileX][tileY]->load(textureID);
		mapObjects[tileX][tileY]->setPosition(float(tileX*32), float(tileY*32));
	}
	else
		cout << "Tower not placed" << endl;
}

//draws map to game window
void Map::draw(sf::RenderWindow& gameWindow){
	for(int tileX = 0; tileX < mapWidth ; ++tileX){
		for(int tileY = 0; tileY < mapHeight ; ++tileY){
			if(tileMap[tileX][tileY] != nullptr)
				tileMap[tileX][tileY]->draw(gameWindow);
			if(mapObjects[tileX][tileY] != nullptr)
				mapObjects[tileX][tileY]->draw(gameWindow);
		}
	}
}