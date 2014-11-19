#pragma once
#include <string>
#include <GameObjects/Towers/ITower.h>

namespace Dec {

class ConcreteTower : public ITower {
	
	static int serial;		// used to increment _id

	public:
		// CONSTRUCTORS
		ConcreteTower();
		ConcreteTower(int tileX, int tileY);
		~ConcreteTower() { std::cout << red << "ConcreteTower has been deleted." << std::endl; }

		// ACCESSORS
		int getID() const;
		int getBuyCost() const;
		int getSellCost() const;

		// MUTATORS
		void setBuyCost(int _buy_cost);
		void setSellCost(int _sell_cost);

		std::string getTowerSpecs();
		void attack();

	private:
		int _id;
		int _tileX;
		int _tileY;
		int _buy_cost;
		int _sell_cost;

};

}