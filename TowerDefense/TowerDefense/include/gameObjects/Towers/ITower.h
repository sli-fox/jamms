#pragma once
#include <string>
#include <sstream>
#include "gameObjects/GameObject.h"

class ITower : public GameObject {
	
	public:
		virtual int getBuyCost() { return 0; };
		virtual std::string getTowerSpecs() = 0;
		virtual ~ITower() = 0;

};

inline ITower::~ITower() { std::cout << red << "ITower has been deleted." << std::endl; }