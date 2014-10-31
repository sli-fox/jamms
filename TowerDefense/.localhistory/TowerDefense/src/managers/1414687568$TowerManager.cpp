#pragma once
#include <Managers/TowerManager.h>
#include <Game.h>
#include <GameObjects/WhiteBloodCellTower.h>
#include <GameObjects/AntibacterialTower.h>
#include <GameObjects/ChemotherapyTower.h>

TowerManager::TowerManager() {};

TowerManager::TowerManager(int mapWidth, int mapHeight) {

	//cout << "Sizeee is: " << tArray.size() << "x" << tArray[0].size() << std::endl;
	this->tArrayRows = mapWidth;
	this->tArrayCols = mapHeight;
}

void TowerManager::setArraySize(int sizeX, int sizeY) {
		vector<vector<Tower*> > tArray(sizeX, vector<Tower*>(sizeY, NULL));
		cout << "Sizeee is: " << tArray.size() << "x" << tArray[0].size() << std::endl;
}

bool TowerManager::isTileFree(int tileX, int tileY) {
	cout << "CHECK 1: " << tileX << "-" << tileY << std::endl;
	if(tArray[tileX][tileY] == NULL) {
		cout << "CHECK 2: " << tileX << "-" << tileY << std::endl;
		return false;
	}
	return false;
}

Tower* TowerManager::getTower(int tileX, int tileY) {
	cout << "Size GSP: " << tArray.size() << "x" << std::endl;
	return tArray[tileX][tileY];
}

bool TowerManager::isMouseInMainWindow(sf::Vector2i mousePos) {
	if(	mousePos.x >= 0 && mousePos.x < tArrayRows
		 && mousePos.y > 0 && mousePos.y < tArrayCols)
		return true;
	return false;
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

Tower* TowerManager::buyTower(Tower::TowerType type, int tileX, int tileY) {
	if(isTileFree(tileX, tileY)) {
	cout << "CHECK 2\n";
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