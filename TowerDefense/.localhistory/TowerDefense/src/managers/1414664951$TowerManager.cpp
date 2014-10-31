#pragma once
#include <TowerManager.h>
#include <Game.h>
#include <WhiteBloodCellTower.h>
#include <AntibacterialTower.h>
#include <ChemotherapyTower.h>

const int tArrayRows = Game::windowWidth/32;
const int tArrayCols = Game::windowHeight/32;



TowerManager::TowerManager() {}

std::vector<std::vector<Tower*> > TowerManager::tArray(tArrayRows, std::vector<Tower*>(tArrayCols, NULL));

bool TowerManager::isTileFree(int tileX, int tileY) {
	if(tArray[tileX][tileY] == NULL)
		return true;
	return false;
}
bool TowerManager::isMouseInMainWindow(sf::Vector2i mousePos) {
	if(	mousePos.x >= 0 && mousePos.x < Game::windowWidth
		 && mousePos.y > 0 && mousePos.y < Game::windowHeight)
		return true;
	return false;
}

void TowerManager::displayTowerArray() {
	std::cout << white;
	for(int i = 0; i < tArrayCols; i++) {
		for(int j = 0; j < tArrayRows; j++) {
			if(isTileFree(j, i))
				std::cout << white << "O" << " ";
			else {
				switch(tArray[j][i]->getType()) {
					case 0:
						std::cout << blue << "W" << " ";
						break;
					case 1:
						std::cout << green << "A" << " ";
						break;
					case 2:
						std::cout << red << "C" << " ";
						break;
					default:
						std::cout << white << "X" << " ";
				}
			}
			
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

Tower* TowerManager::buyTower(Tower::TowerType type, sf::Vector2i mousePos) {
	int tileX = mousePos.x/32;
	int tileY = mousePos.y/32;
	if(isTileFree(tileX, tileY)) {
		switch(type) {
			case 0: {
				if(WhiteBloodCellTower::buy_cost <= Tower::getWallet()) {
					tArray[tileX][tileY] = new WhiteBloodCellTower(mousePos);
					Tower::updateWallet(- WhiteBloodCellTower::buy_cost);
					std::cout << blue << tArray[tileX][tileY]->getName() << " bought for "
						<< WhiteBloodCellTower::buy_cost
						<< " coins!" << white << std::endl;
				}
				else {
					std::cout << red << "Insufficient funds." << std::endl;
					return NULL;
				}
				break;
			}
			case 1: {
				if(AntibacterialTower::buy_cost <= Tower::getWallet()) {
					tArray[tileX][tileY] = new AntibacterialTower(mousePos);
					Tower::updateWallet(- AntibacterialTower::buy_cost);
					std::cout << blue << tArray[tileX][tileY]->getName() << " bought for "
						<< AntibacterialTower::buy_cost
						<< " coins!" << white << std::endl;
				}
				else {
					std::cout << red << "Insufficient funds." << std::endl;
					return NULL;
				}
				break;
			}
			case 2: {
				if(ChemotherapyTower::buy_cost <= Tower::getWallet()) {
					tArray[tileX][tileY] = new ChemotherapyTower(mousePos);
					Tower::updateWallet(- ChemotherapyTower::buy_cost);
					std::cout << blue << tArray[tileX][tileY]->getName() << " bought for "
						<< ChemotherapyTower::buy_cost
						<< " coins!" << white << std::endl;
				}
				else {
					std::cout << red << "Insufficient funds." << std::endl;
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