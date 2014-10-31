#pragma once
#include <Managers/TowerManager.h>
#include <Game.h>
#include <GameObjects/ShihTzu.h>
#include <GameObjects/Dalmatian.h>
#include <GameObjects/Bulldog.h>


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
	if(!outOfBound(tileX, tileY) && tArray[tileX][tileY] == NULL) {
		return true;
	}
	return false;
}

Tower* TowerManager::getTower(int tileX, int tileY) {
	if(!outOfBound(tileX, tileY) && tArray[tileX][tileY] != NULL)
		return tArray[tileX][tileY];
	return NULL;	// this line should never be reached
}

bool TowerManager::outOfBound(int tileX, int tileY) {
	return (!(-1 < tileX && tileX < tArrayRows) || !(-1 < tileY && tileY < tArrayCols));
}

Tower* TowerManager::buyTower(Tower::TowerType type, int tileX, int tileY) {
	if(!outOfBound(tileX, tileY) && isTileFree(tileX, tileY)) {
		switch(type) {
			case 0: {
				if(ShihTzu::buy_cost <= Tower::getWallet()) {
					TowerManager::tArray[tileX][tileY] = new ShihTzu(tileX, tileY);
					Tower::updateWallet(- ShihTzu::buy_cost);
					cout << blue << tArray[tileX][tileY]->getName() << " bought for "
						<< ShihTzu::buy_cost
						<< " coins!" << white << std::endl;
				}
				else {
					cout << red << "Insufficient funds." << std::endl;
					return NULL;
				}
				break;
			}
			case 1: {
				if(Dalmatian::buy_cost <= Tower::getWallet()) {
					tArray[tileX][tileY] = new Dalmatian(tileX, tileY);
					Tower::updateWallet(- Dalmatian::buy_cost);
					cout << blue << tArray[tileX][tileY]->getName() << " bought for "
						<< Dalmatian::buy_cost
						<< " coins!" << white << std::endl;
				}
				else {
					cout << red << "Insufficient funds." << std::endl;
					return NULL;
				}
				break;
			}
			case 2: {
				if(Bulldog::buy_cost <= Tower::getWallet()) {
					tArray[tileX][tileY] = new Bulldog(tileX, tileY);
					Tower::updateWallet(- Bulldog::buy_cost);
					cout << blue << tArray[tileX][tileY]->getName() << " bought for "
						<< Bulldog::buy_cost
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
	if(!outOfBound(tileX, tileY) && isTileFree(tileX, tileY))
		return;
	Tower::updateWallet(+ tArray[tileX][tileY]->getSellCost());
	std::cout << blue << tArray[tileX][tileY]->getName() << " sold for "
		<< tArray[tileX][tileY]->getSellCost()
		<< " coins!" << white << std::endl;
	delete tArray[tileX][tileY];
	tArray[tileX][tileY] = NULL;
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

void TowerManager::displayTowerRange(int tileX, int tileY, sf::RenderWindow& gameWindow) {
	if(!outOfBound(tileX, tileY) && !isTileFree(tileX, tileY)) {
		gameWindow.draw(tArray[tileX][tileY]->getRangeShape());
		std::cout << "showing rangee" << std::endl;
	}

}

//draws tower to game window
void TowerManager::draw(sf::RenderWindow& gameWindow){
	for(int tileX = 0; tileX < tArrayRows ; ++tileX){
		for(int tileY = 0; tileY < tArrayCols ; ++tileY){
			if(tArray[tileX][tileY] != NULL) {
				tArray[tileX][tileY]->draw(gameWindow);
			}
		}
	}
}
