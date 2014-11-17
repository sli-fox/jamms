#pragma once
#include "gameObjects/Critter.h"
#include <math.h>

class TowerStrategy{
public:
	virtual Critter* computeTarget(Critter* critter1, Critter* critter2, GameObject* tower) = 0;
};

class NearestTowerStrategy: public TowerStrategy {
public:
	inline Critter* computeTarget(Critter* critter1, Critter* critter2, GameObject* tower){
		//using mathematical formula for distance
		float distance1, distance2;
		distance1 = sqrt(pow(critter1->getPosition().x  - tower->getPosition().x, 2) + pow(critter1->getPosition().y  - tower->getPosition().y, 2));
		distance2 = sqrt(pow(critter2->getPosition().x  - tower->getPosition().x, 2) + pow(critter2->getPosition().y  - tower->getPosition().y, 2));
		if(distance1 < distance2)
			return  critter1;
		else
			return critter2;
	}
};

class NearestEndPointStrategy: public TowerStrategy {
public:
	inline Critter* computeTarget(Critter* critter1, Critter* critter2, GameObject* tower){
		if(critter1->getId() < critter2->getId())
			return  critter1;
		else
			return critter2;
	}
};

class NearestStartPointStrategy: public TowerStrategy {
public:
	inline Critter* computeTarget(Critter* critter1, Critter* critter2, GameObject* tower){
		if(critter1->getId() > critter2->getId())
			return  critter1;
		else
			return critter2;
	}
};

class StrongestStrategy: public TowerStrategy {
public:
	inline Critter* computeTarget(Critter* critter1, Critter* critter2, GameObject* tower){
		if(critter1->getStealPointsStrength() > critter2->getStealPointsStrength())
			return  critter1;
		else
			return critter2;
	}
};

class WeakestStrategy: public TowerStrategy {
public:
	inline Critter* computeTarget(Critter* critter1, Critter* critter2, GameObject* tower){
		if(critter1->getStealPointsStrength() < critter2->getStealPointsStrength())
			return  critter1;
		else
			return critter2;
	}
};

class MostHealthStrategy: public TowerStrategy {
public:
	inline Critter* computeTarget(Critter* critter1, Critter* critter2, GameObject* tower){
		if(critter1->getHitPoints() > critter2->getHitPoints())
			return  critter1;
		else
			return critter2;
	}
};

class LeastHealthStrategy: public TowerStrategy {
public:
	inline Critter* computeTarget(Critter* critter1, Critter* critter2, GameObject* tower){
		if(critter1->getHitPoints() < critter2->getHitPoints())
			return  critter1;
		else
			return critter2;
	}
};

class SlowestStrategy: public TowerStrategy {
public:
	inline Critter* computeTarget(Critter* critter1, Critter* critter2, GameObject* tower){
		if(critter1->getSpeed() < critter2->getSpeed())
			return  critter1;
		else
			return critter2;
	}
};

class FastestStrategy: public TowerStrategy {
public:
	inline Critter* computeTarget(Critter* critter1, Critter* critter2, GameObject* tower){
		if(critter1->getSpeed() > critter2->getSpeed())
			return  critter1;
		else
			return critter2;
	}
};

class MostCoinsStrategy: public TowerStrategy {
public:
	inline Critter* computeTarget(Critter* critter1, Critter* critter2, GameObject* tower){
		if(critter1->getPlayerReward() > critter2->getPlayerReward())
			return  critter1;
		else
			return critter2;
	}
};