#pragma once
#include "gameObjects/TowerDecorator.h"

TowerDecorator::TowerDecorator() {}
TowerDecorator::TowerDecorator(Tower* tower) : _decoratedTower(tower) {}
TowerDecorator::~TowerDecorator() {}