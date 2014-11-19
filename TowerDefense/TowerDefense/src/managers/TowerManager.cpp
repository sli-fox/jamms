#pragma once
#include <Managers/TowerManager.h>

TowerManager::TowerManager(int mapWidth, int mapHeight) {
	tArrayRows = mapWidth;
	tArrayCols = mapHeight;
}

void TowerManager::clearAllTowers() {
	while(!towers.empty()) {
		delete towers.begin()->second;
		towers.erase(towers.begin()->first);
	}
}

bool TowerManager::isTileFree(int tileX, int tileY) {
	if(towers[std::make_pair(tileX,tileY)] == NULL)
		return true;
	return false;
}


map<pair<int,int>, Tower*> * TowerManager::getTowerMap() {
	return &towers;
}

Tower* TowerManager::getTower(int tileX, int tileY) {
	if(towers[make_pair(tileX, tileY)] != NULL)
		return towers[make_pair(tileX, tileY)];
	return NULL;	// this line should never be reached
}

bool TowerManager::outOfBound(int tileX, int tileY) const {
	return (!(-1 < tileX && tileX < tArrayRows) || !(-1 < tileY && tileY < tArrayCols));
}

Tower* TowerManager::buyTower(Tower::TowerType type, int tileX, int tileY) {
	if(isTileFree(tileX, tileY) && type <= 2) {
		switch(type) {
			case 0: {
				if(ShihTzu::buy_cost <= Game::player.getCash())
					towers[make_pair(tileX, tileY)] = new ShihTzu(tileX, tileY);
				else {
					cout << red << "Insufficient funds." << std::endl;
					return NULL;
				}
				break;
			}
			case 1: {
				if(Dalmatian::buy_cost <= Game::player.getCash())
					towers[make_pair(tileX, tileY)] = new Dalmatian(tileX, tileY);
				else {
					cout << red << "Insufficient funds." << std::endl;
					return NULL;
				}
				break;
			}
			case 2: {
				if(Bulldog::buy_cost <= Game::player.getCash())
					towers[make_pair(tileX, tileY)] = new Bulldog(tileX, tileY);
				else {
					cout << red << "Insufficient funds." << std::endl;
					return NULL;
				}
				break;
			}
		}
		Game::player.spendCash(towers[make_pair(tileX, tileY)]->getBuyCost());
		cout << blue << "Tower bought for " << towers[make_pair(tileX, tileY)]->getBuyCost() << "  coins!" << std::endl;
		return towers[make_pair(tileX, tileY)];
	} else {
		std::cerr << red << "Error: There is already a tower on this cell." << std::endl;
	}
	return NULL;
}

ITower* TowerManager::DecBuyTower(int tileX, int tileY) {
	Dec::ConcreteTower* ct = new Dec::FreezeEffect(new Dec::TowerDecorator(new Dec::ConcreteTower(tileX, tileY)));
	ct->getTowerSpecs();
	ct->attack();
	Dtowers[make_pair(tileX, tileY)] = ct;
	return Dtowers[make_pair(tileX, tileY)];
}

void TowerManager::sellTower(int tileX, int tileY)  {
	if(!outOfBound(tileX, tileY) && isTileFree(tileX, tileY))
		return;
	Game::player.earnCash(towers[make_pair(tileX, tileY)]->getSellCost());
	std::cout << blue << towers[make_pair(tileX, tileY)]->getName() << " sold for "
		<< towers[make_pair(tileX, tileY)]->getSellCost()
		<< " coins!" << std::endl;
	delete towers[make_pair(tileX, tileY)];
	towers.erase(make_pair(tileX, tileY));
}

//draws tower to game window
void TowerManager::draw(sf::RenderWindow& gameWindow){
	for(std::map<std::pair<int,int>, Tower*>::iterator it = towers.begin() ; it != towers.end() ; ++it) {
		if(it->second != NULL)
			it->second->draw(gameWindow);
	}
	
	for(std::map<std::pair<int,int>, ITower*>::iterator it = Dtowers.begin() ; it != Dtowers.end() ; ++it) {
		if(it->second != NULL)
			it->second->draw(gameWindow);
	}
}