#pragma once
#include <string>
#include <sstream>
#include <GameObjects/Towers/ITower.h>

class DTower : public ITower {
	
		static int DTower::serial;		// used to increment _id

	public:
		// CONSTRUCTORS
		DTower();
		DTower(int tileX, int tileY);
		~DTower() { std::cout << red << "DTower #" << this->D_id << " has been deleted." << std::endl; }

		// ACCESSORS
		int DgetID() const;
		int DgetBuyCost() const;
		int DgetSellCost() const;

		// MUTATORS
		void DsetSellCost(int _sell_cost);

		std::string DgetTowerSpecs();


	private:
		int D_id;
		int D_tileX;
		int D_tileY;
		int D_buy_cost;
		int D_sell_cost;

};