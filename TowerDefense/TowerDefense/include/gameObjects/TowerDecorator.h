#pragma once
#include <GameObjects/Tower.h>

class TowerDecorator : public Tower {

public:
	TowerDecorator();
	TowerDecorator(Tower* tower);
	~TowerDecorator();

protected:
	Tower* _decoratedTower;
};