#pragma once
#include <GameObjects/FreezeEffect.h>

FreezeEffect::FreezeEffect() {}

FreezeEffect::FreezeEffect(Tower* tower) : _decoratedTower(tower) {
	this->load("resources/images/towers/icetower.png");
	this->setPosition(tower->getPosition().first, tower->getPosition().second);		// has to be set BEFORE setRange();

	this->_id = tower->getID();
	this->_name = tower->getName();
	this->_type = tower->getType();
	this->_upgrade_level = tower->getUpgradeLevel();
	this->_buy_cost = tower->getBuyCost();
	this->_power = tower->getPower();
	this->setRange(tower->getRange());
	this->_rate_of_fire = tower->getRateOfFire();
	this->_upgrade_cost = tower->getUpgradeCost();
	this->_sell_cost = tower->getSellCost();
	this->_target = tower->getTarget();
}

void FreezeEffect::attack() {
	_decoratedTower->attack();
	this->_target = _decoratedTower->getTarget();
	//cout << red << this->getName() << " is Applying Freezing Effect to Critter " << this->getTarget()->getId() << endl;
	this->_target->setSpeed(0);
			/*
			critter->isFrozen;
			
			float speedBeforeFrozen = critter->getSpeed();
			cout << "speed before frozen " << speedBeforeFrozen << endl;

			critter->setSpeed(0);
			cout << "speed after frozen " << critter->getSpeed() << endl;
			*/


			/*
			this->time = this->clock.getElapsedTime();

			while(this->time.asSeconds() * this->getRateOfFire() >= 1) {
				cout << "Unfreezing " << endl;
				critter->setSpeed(0);
				this->clock.restart();
				//critter->setSpeed(0);
			}
			*/
			

			/*
			this->time = this->clock.getElapsedTime();
			cout << "frozen time in seconds " << time.asSeconds() << endl;
			
			while(time.asSeconds() <= 3) {
				critter->setSpeed(0.0f);
				
				time += clock.getElapsedTime();
				cout << "frozen time in seconds + more elapsed time " << time.asSeconds() << endl;
			}
			*/


			/*
			int delayCount = 0;

			while (critter->getSpeed() == 0) {
				cout << "Delay Count: " << delayCount << endl;
				if (delayCount >= 500) {
					cout << "Delay Count >= 500" << endl;
					critter->setSpeed(speedBeforeFrozen);
				}
				delayCount += 1;
			}
			*/


			/*
			critter->setSpeed(speedBeforeFrozen);
			cout << "speed completing frozen " << critter->getSpeed() << endl;
			*/
			//cout << red << "Unfreezing Critter " << this->getTarget()->getId() << endl;
}

// @Override
std::string FreezeEffect::getTowerSpecs() {
	std::stringstream output;
	output << _decoratedTower->getTowerSpecs();
	output << "Special Effect: Freezing" << std::endl;
	return output.str();
}