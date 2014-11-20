#pragma once
#include <GameObjects/Tower.h>

class TowerDecorator : public Tower {
	
	public:
		TowerDecorator();
		~TowerDecorator() { std::cout << red << "TowerDecorator has been deleted." << std::endl; }

};