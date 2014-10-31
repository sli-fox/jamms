#pragma once
#include <Managers/TowerManager.h>
#include <Game.h>
#include <GameObjects/WhiteBloodCellTower.h>
#include <GameObjects/AntibacterialTower.h>
#include <GameObjects/ChemotherapyTower.h>

TowerManager::TowerManager() {};
//TowerManager::TowerManager(int mapWidth, int mapHeight) {
//	vector<vector<Tower*> > tArray(mapWidth, vector<Tower*>(mapHeight, NULL));
//	cout << "Tower Array initialized to: " << tArray.size() << "x" << tArray[0].size() << std::endl;;
//	this->tArrayRows = mapWidth;
//	this->tArrayCols = mapHeight;
//}


void TowerManager::setArraySize(int mapWidth, int mapHeight) {
	this->tArrayRows = mapWidth;
	this->tArrayCols = mapHeight;

	//resize 1st dimension of vector to mapWidth (number of tiles width-wise)
	tArray.resize(mapWidth);

	//resize 2nd dimension of vector to mapHeight(number of tiles height-wise)
	for(int i = 0; i < tArrayRows; ++i)
		tArray.at(i).resize(tArrayCols);
}

bool TowerManager::isTileFree(int tileX, int tileY) {
	if(tArray[tileX][tileY] == NULL) {
		return true;
	}
	return false;
}

Tower* TowerManager::getTower(int tileX, int tileY) {
	if(tArray[tileX][tileY] != NULL)
		return tArray[tileX][tileY];
	return NULL;	// this line should never be reached
}

bool TowerManager::outOfBound(int tileX, int tileY) {
	return (!(-1 < tileX && tileX < tArrayRows) || !(-1 < tileY && tileY < tArrayCols));
}

Tower* TowerManager::buyTower(Tower::TowerType type, int tileX, int tileY) {
	if(isTileFree(tileX, tileY)) {
		switch(type) {
			case 0: {
				if(WhiteBloodCellTower::buy_cost <= Tower::getWallet()) {
					TowerManager::tArray[tileX][tileY] = new WhiteBloodCellTower(tileX, tileY);
					Tower::updateWallet(- WhiteBloodCellTower::buy_cost);
					cout << blue << tArray[tileX][tileY]->getName() << " bought for "
						<< WhiteBloodCellTower::buy_cost
						<< " coins!" << white << std::endl;
				}
				else {
					cout << red << "Insufficient funds." << std::endl;
					return NULL;
				}
				break;
			}
			case 1: {
				if(AntibacterialTower::buy_cost <= Tower::getWallet()) {
					tArray[tileX][tileY] = new AntibacterialTower(tileX, tileY);
					Tower::updateWallet(- AntibacterialTower::buy_cost);
					cout << blue << tArray[tileX][tileY]->getName() << " bought for "
						<< AntibacterialTower::buy_cost
						<< " coins!" << white << std::endl;
				}
				else {
					cout << red << "Insufficient funds." << std::endl;
					return NULL;
				}
				break;
			}
			case 2: {
				if(ChemotherapyTower::buy_cost <= Tower::getWallet()) {
					tArray[tileX][tileY] = new ChemotherapyTower(tileX, tileY);
					Tower::updateWallet(- ChemotherapyTower::buy_cost);
					cout << blue << tArray[tileX][tileY]->getName() << " bought for "
						<< ChemotherapyTower::buy_cost
						<< " coins!" << white << std::endl;
				}
				else {
					cout << red << "Insufficient funds." << std::endl;
					return NULL;
				}
				break;
			}
		}
		return tArray[tileX][tileY];
	} else {
		std::cerr << red << "Error: There is already a tower on this cell." << std::endl;
	}
	return NULL;
}

void TowerManager::sellTower(int tileX, int tileY)  {
	Tower::updateWallet(+ tArray[tileX][tileY]->getSellCost());
	std::cout << blue << tArray[tileX][tileY]->getName() << " sold for "
		<< tArray[tileX][tileY]->getSellCost()
		<< " coins!" << white << std::endl;
}

void TowerManager::displayTowerArray() {
	cout << white;
	for(int i = 0; i < tArrayCols; i++) {
		for(int j = 0; j < tArrayRows; j++) {
			if(isTileFree(j, i))
				cout << white << "O" << " ";
			else {
				switch(tArray[j][i]->getType()) {
					case 0:
						cout << blue << "W" << " ";
						break;
					case 1:
						cout << green << "A" << " ";
						break;
					case 2:
						cout << red << "C" << " ";
						break;
					default:
						cout << white << "X" << " ";
				}
			}
			
		}
		cout << std::endl;
	}
	cout << std::endl;
}

//draws map to game window
void TowerManager::draw(sf::RenderWindow& gameWindow){
	for(int tileX = 0; tileX < tArrayRows ; ++tileX){
		for(int tileY = 0; tileY < tArrayCols ; ++tileY){
			if(tArray[tileX][tileY] != nullptr)
				tArray[tileX][tileY]->draw(gameWindow);
	}
}
}
