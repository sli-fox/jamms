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
				if(ConcreteTower::buy_cost <= Game::player.getCash())
					towers[make_pair(tileX, tileY)] = new FreezeEffect(new ConcreteTower(tileX, tileY));
				else {
					cout << red << "Insufficient funds." << std::endl;
					return NULL;
				}
				break;
			}
			case 1: {
				if(ConcreteTower::buy_cost <= Game::player.getCash())
					towers[make_pair(tileX, tileY)] = new ConcreteTower(tileX, tileY);
				else {
					cout << red << "Insufficient funds." << std::endl;
					return NULL;
				}
				break;
			}
			case 2: {
				if(ConcreteTower::buy_cost <= Game::player.getCash())
					towers[make_pair(tileX, tileY)] = new BurnEffect(new ConcreteTower(tileX, tileY));
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

void TowerManager::upgradeTower(int tileX, int tileY, std::string upgrade) {
	if(!outOfBound(tileX, tileY) && isTileFree(tileX, tileY))
		return;
	if(upgrade == "ice")
		towers[make_pair(tileX, tileY)] = new FreezeEffect(towers[make_pair(tileX, tileY)]);
	if(upgrade == "fire")
		towers[make_pair(tileX, tileY)] = new BurnEffect(towers[make_pair(tileX, tileY)]);
	if(upgrade == "range")
		towers[make_pair(tileX, tileY)]->setRange(towers[make_pair(tileX, tileY)]->getRange()+0.5);

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
}