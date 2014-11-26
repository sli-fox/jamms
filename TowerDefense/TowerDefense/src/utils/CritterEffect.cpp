#pragma once
#include "utils/CritterEffect.h"

CritterEffect::CritterEffect(int damage, float speedModifier, int stacks, float cycles){
	this->damage = damage;
	this->speedModifier = speedModifier;
	this->stacks = stacks;
	this->cycles = cycles;
	elapsedTicks = cycles;
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

float CritterEffect::getDelay(){
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

bool CritterEffect::isEqual(CritterEffect effect){
	return this->damage == effect.damage
		&& this->speedModifier == effect.speedModifier
		&& this->cycles == effect.cycles;
}