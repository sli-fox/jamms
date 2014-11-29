#pragma once
#include "utils/CritterEffect.h"
#include <iostream>

CritterEffect::CritterEffect(){}

CritterEffect::CritterEffect(int damage, float speedModifier, int stacks, float cycles){
	this->damage = damage;
	this->speedModifier = speedModifier;
	this->stacks = stacks;
	this->cycles = cycles;
	elapsedTicks = cycles;
	type = NONE;
}

CritterEffect::~CritterEffect(){

}

bool CritterEffect::applyEffect(){
	if(elapsedTicks >= cycles){
		--stacks;
		elapsedTicks = 0;
		return true;
	}
	else
		return false;
}

int CritterEffect::getDamage(){
	return damage;
}

float CritterEffect::getSpeedModifer(){
	return speedModifier;
}

int CritterEffect::getStacks(){
	return stacks;
}

float CritterEffect::getCycles(){
	return cycles;
}

float CritterEffect::getElapsedTicks(){
	return elapsedTicks;
}

void CritterEffect::addStacks(int stacks){
	this->stacks += stacks;
}

void CritterEffect::tick(){
	elapsedTicks += 1.00;
}

bool CritterEffect::isEqual(CritterEffect* effect){
	return this->type == effect->type;
}

//applies two stacks of burning which tick for 1 damage each every 2 seconds
Burn::Burn(){
	this->damage = 1;
	this->speedModifier = 1.0;
	this->stacks = 2;
	this->cycles = 100;
	elapsedTicks = cycles;
	type = BURN;
}
Burn::~Burn(){}

//progressively slows critter as stacks build until speed is 0, then regains speed as stacks drop off
Freeze::Freeze(){
	this->damage = 0;
	this->speedModifier = 1.0;
	this->stacks = 2;
	this->cycles = 100;
	elapsedTicks = cycles;
	type = FREEZE;
}
Freeze::~Freeze(){}

int Freeze::getDamage(){
	/*damage = 0;
	for (int i = 5 ; i <= stacks ; i += 5){
		damage += 1;
		if(i == 10)
			break;
	}
	std::cout << "stacks: " << stacks << std::endl;
	*/
	return damage;
}

float Freeze::getSpeedModifer(){
	speedModifier = 1.0;
	for (int i = 1 ; i <= stacks ; ++i){
		speedModifier -= 0.2f;
		if(i == 5)
			break;
	}
	if (stacks > 5)
		stacks = 5;
	return speedModifier;
}

Slowe::Slowe(){
	this->damage = 0;
	this->speedModifier = 0.5;
	this->stacks = 1;
	this->cycles = 150;
	elapsedTicks = cycles;
	type = SLOW;
}

Slowe::~Slowe(){}

//stuns target for about 1.5 seconds and ticks damage rapidly while stunned
Crush::Crush(){
	this->damage = 1;
	this->speedModifier = 0;
	this->stacks = 2;
	this->cycles = 15;
	elapsedTicks = cycles;
	type = CRUSH;
}
Crush::~Crush(){}

int Crush::getDamage(){
	if(stacks > 2){
		stacks = 0;
	}
	return damage;
}

//stuns target for about 1 second
Stun::Stun(){
	this->damage = 0;
	this->speedModifier = 0;
	this->stacks = 1;
	this->cycles = 60;
	elapsedTicks = cycles;
	type = STUN;
}
Stun::~Stun(){}

//knocks target back for about 1 second
Knockback::Knockback(){
	this->damage = 0;
	this->speedModifier = -2;
	this->stacks = 1;
	this->cycles = 50;
	elapsedTicks = cycles;
	type = KNOCKBACK;
}
Knockback::~Knockback(){}

/*NOT YET IMPLEMENTED

class Petrify : public CritterEffect {
	Petrify();
	virtual ~Petrify();
	virtual float getSpeedModifer();
};

struct Poison : public CritterEffect {
	Poison();
	virtual ~Poison();
};

struct Shock : public CritterEffect {
	Shock();
	virtual ~Shock();
};

struct Moonwalk : public CritterEffect {
	Moonwalk();
	virtual ~Moonwalk();
};
*/