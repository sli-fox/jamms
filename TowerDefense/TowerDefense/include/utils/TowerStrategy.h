#pragma once
#include "gameObjects/Critter.h"
#include <math.h>
#include <deque>

class TowerStrategy{
public:
	inline virtual Critter* computeTarget(Critter* critter1, Critter* critter2, std::pair<float,float> towerPosition) = 0;
	inline virtual std::string getName() const = 0;
};

class NearestTowerStrategy: public TowerStrategy {
public:
	inline Critter* computeTarget(Critter* critter1, Critter* critter2, std::pair<float,float> towerPosition){
		//using mathematical formula for distance
		float distance1, distance2;
		distance1 = sqrt(pow(critter1->getPosition().first  - towerPosition.first, 2) + pow(critter1->getPosition().second  - towerPosition.second, 2));
		distance2 = sqrt(pow(critter2->getPosition().first  - towerPosition.first, 2) + pow(critter2->getPosition().second  - towerPosition.second, 2));
		if(distance1 < distance2)
			return  critter1;
		else
			return critter2;
	}
	inline virtual std::string getName() const{
		return "Nearest Tower";
	}
};

class NearestEndPointStrategy: public TowerStrategy {
public:
	inline Critter* computeTarget(Critter* critter1, Critter* critter2, std::pair<float,float> towerPosition){
		if(!critter1->isActive || critter1 == nullptr)
			return critter2;
		else if(!critter2->isActive || critter2 == nullptr)
			return critter1;
		else if(critter1 == nullptr && critter2 == nullptr)
			return nullptr;

		int critter1posX = int(critter1->getPosition().first / 32);
		int critter1posY = int(critter1->getPosition().second / 32);
		int critter2posX = int(critter2->getPosition().first / 32);
		int critter2posY = int(critter2->getPosition().second / 32);

		std::deque<const Tile* const> mapPath = Game::map.getMapPath();
		std::ptrdiff_t critter1Index = 0;
		std::ptrdiff_t critter2Index = 0;
		
		std::deque<const Tile* const>::const_reverse_iterator it = mapPath.crbegin();
		
		for(it ; it < mapPath.crend() ; ++it) {
			if((*it)->getTileX() == int(critter1posX) && (*it)->getTileY() == int(critter1posY))
				critter1Index = std::distance(mapPath.crbegin(), it);

			if((*it)->getTileX() == int(critter2posX) && (*it)->getTileY() == int(critter2posY))
				critter2Index = std::distance(mapPath.crbegin(), it);
		}
		//compares which critter is closest to the end tile
		if(int(critter1Index) < int(critter2Index)){
			return critter1;
		}
		else
			return critter2;
	}
	inline virtual std::string getName() const{
		return "Nearest End Point";
	}
};

class StrongestStrategy: public TowerStrategy {
public:
	inline Critter* computeTarget(Critter* critter1, Critter* critter2, std::pair<float,float> towerPosition){
		if(critter1->getStealPointsStrength() > critter2->getStealPointsStrength())
			return  critter1;
		else
			return critter2;
	}
	inline virtual std::string getName() const{
		return "Strongest Critter";
	}
};

class WeakestStrategy: public TowerStrategy {
public:
	inline Critter* computeTarget(Critter* critter1, Critter* critter2, std::pair<float,float> towerPosition){
		if(critter1->getStealPointsStrength() < critter2->getStealPointsStrength())
			return  critter1;
		else
			return critter2;
	}
	inline virtual std::string getName() const{
		return "Weakest Critter";
	}
};

class MostHealthStrategy: public TowerStrategy {
public:
	inline Critter* computeTarget(Critter* critter1, Critter* critter2, std::pair<float,float> towerPosition){
		if(critter1->getHitPoints() > critter2->getHitPoints())
			return  critter1;
		else
			return critter2;
	}
	inline virtual std::string getName() const{
		return "Most Health";
	}
};

class LeastHealthStrategy: public TowerStrategy {
public:
	inline Critter* computeTarget(Critter* critter1, Critter* critter2, std::pair<float,float> towerPosition){
		if(critter1->getHitPoints() < critter2->getHitPoints())
			return  critter1;
		else
			return critter2;
	}
	inline virtual std::string getName() const{
		return "Least Health";
	}
};

class SlowestStrategy: public TowerStrategy {
public:
	inline Critter* computeTarget(Critter* critter1, Critter* critter2, std::pair<float,float> towerPosition){
		if(critter1->getSpeed() < critter2->getSpeed())
			return  critter1;
		else
			return critter2;
	}
	inline virtual std::string getName() const{
		return "Slowest";
	}
};

class FastestStrategy: public TowerStrategy {
public:
	inline Critter* computeTarget(Critter* critter1, Critter* critter2, std::pair<float,float> towerPosition){
		if(critter1->getSpeed() > critter2->getSpeed())
			return  critter1;
		else
			return critter2;
	}
	inline virtual std::string getName() const{
		return "Fastest";
	}
};

class MostCoinsStrategy: public TowerStrategy {
public:
	inline Critter* computeTarget(Critter* critter1, Critter* critter2, std::pair<float,float> towerPosition){
		if(critter1->getPlayerReward() > critter2->getPlayerReward())
			return  critter1;
		else
			return critter2;
	}
	inline virtual std::string getName() const{
		return "Most Coins";
	}
};