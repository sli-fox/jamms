#pragma once
#include <GameObjects/Towers/ITower.h>
#include <GameObjects/Towers/ConcreteTower.h>

namespace Dec {

	class TowerDecorator : public Dec::ConcreteTower {
	
	public:
		TowerDecorator() {}
		TowerDecorator(ITower* decoratedTower);
		~TowerDecorator() { std::cout << red << "TowerDecorator has been deleted." << std::endl; }

		// ACCESSORS
		int getPower() const;
		int getSpeed() const;
		float getRange() const;

		// MUTATORS
		void setPower(int power);
		void setSpeed(int speed);
		void setRange(float range);
		
		std::string getTowerSpecs();

	private:
		ITower* _decoratedTower;
		int _power;
		int _speed;
		float _range;

};

}