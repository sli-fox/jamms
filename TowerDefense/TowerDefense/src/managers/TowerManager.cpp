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
	if(towers[make_pair(tileX,tileY)] == NULL)
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

Tower* TowerManager::buyTower(std::string towerSelector, int tileX, int tileY) {
	if(towerSelector == "") return NULL;
	if(isTileFree(tileX, tileY)) {
		if(towerSelector == "BabyShihTzu") {
			if(BabyShihTzu::buy_cost <= Game::player.getCash()) {
				towers[make_pair(tileX, tileY)] = new BabyShihTzu(tileX, tileY);
			}
			else return NULL;
		}
		if(towerSelector == "BabyDalmatian") {
			if(BabyDalmatian::buy_cost <= Game::player.getCash())
				towers[make_pair(tileX, tileY)] = new BabyDalmatian(tileX, tileY);
			else return NULL;
		}
		if(towerSelector == "BabyBulldog") {
			if(BabyBulldog::buy_cost <= Game::player.getCash())
				towers[make_pair(tileX, tileY)] = new BabyBulldog(tileX, tileY);
			else return NULL;
		}

		Game::player.spendCash(towers[make_pair(tileX, tileY)]->getBuyCost());
		cout << blue << "Tower bought for " << towers[make_pair(tileX, tileY)]->getBuyCost() << "  coins!" << std::endl;
		return towers[make_pair(tileX, tileY)];
	} else {
		std::cerr << red << "Error: There is already a tower on this cell." << std::endl;
	}
	return NULL;
}

void TowerManager::upgradeTower(int tileX, int tileY) {
	int upgradeCost = -1;
	Tower* tower = towers[make_pair(tileX, tileY)];
	if(tower->getType() == Tower::TowerType::ShihTzu) {
		if(tower->getUpgradeLevel() == Tower::UpgradeLevel::Baby && TeenShihTzuUpgrade::teen_upgrade_cost <= Game::player.getCash()) {
			tower = new TeenShihTzuUpgrade(tower);
			upgradeCost = TeenShihTzuUpgrade::teen_upgrade_cost;
		}
		else if(tower->getUpgradeLevel() == Tower::UpgradeLevel::Teen && AdultShihTzuUpgrade::adult_upgrade_cost <= Game::player.getCash()) {
			tower = new FreezeEffect(new AdultShihTzuUpgrade(tower));
			upgradeCost = AdultShihTzuUpgrade::adult_upgrade_cost;
		}
	}
	if(tower->getType() == Tower::TowerType::Dalmatian) {
		if(tower->getUpgradeLevel() == Tower::UpgradeLevel::Baby && TeenDalmatianUpgrade::teen_upgrade_cost <= Game::player.getCash()) {
			tower = new TeenDalmatianUpgrade(tower);
			upgradeCost = TeenDalmatianUpgrade::teen_upgrade_cost;
		}
		else if(tower->getUpgradeLevel() == Tower::UpgradeLevel::Teen && AdultDalmatianUpgrade::adult_upgrade_cost <= Game::player.getCash()) {
			tower = new SlowEffect(new AdultDalmatianUpgrade(tower));
			upgradeCost = AdultDalmatianUpgrade::adult_upgrade_cost;
		}
	}
	if(tower->getType() == Tower::TowerType::Bulldog) {
		if(tower->getUpgradeLevel() == Tower::UpgradeLevel::Baby && TeenBulldogUpgrade::teen_upgrade_cost <= Game::player.getCash()) {
			tower = new TeenBulldogUpgrade(tower);
			upgradeCost = TeenBulldogUpgrade::teen_upgrade_cost;
		}
		else if(tower->getUpgradeLevel() == Tower::UpgradeLevel::Teen && AdultBulldogUpgrade::adult_upgrade_cost <= Game::player.getCash()) {
			tower = new BurnEffect(new AdultBulldogUpgrade(tower));
			upgradeCost = AdultBulldogUpgrade::adult_upgrade_cost;
		}
	}
	if(upgradeCost != -1) {
		towers[make_pair(tileX, tileY)] = tower;
		Game::player.spendCash(upgradeCost);
	}
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