#pragma once
#include <GameObjects/Towers/ITower.h>

class TowerUpgrades : public ITower {
	
	public:
		enum Range { Small = 1, Medium, Large };

		// ACCESSORS
		int getPower() const;
		int getSpeed() const;
		TowerUpgrades::Range getRange() const;

		// MUTATORS
		void setPower(int power);
		void setSpeed(int speed);
		void setRange(TowerUpgrades::Range range);


	protected:
		int power;
		int speed;
		TowerUpgrades::Range range;

};