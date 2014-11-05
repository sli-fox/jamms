#include "gameObjects/Critter.h"
#include "Game.h"
#include <math.h>
#include <deque>

struct ClosestToEndTile {

	/**
	  * @brief Comparator which determines the critter closest to the end tile. Compares distance by path index relative to end tile, not by pixel distance.
	  * @return bool
	  */
    bool inline operator()(Critter* const & critter1, Critter* const & critter2) {
        
		//gets path position based on pixel coordinates
		int critter1posX = int(critter1->getPosition().x / 32);
		int critter1posY = int(critter1->getPosition().y / 32);
		int critter2posX = int(critter2->getPosition().x / 32);
		int critter2posY = int(critter2->getPosition().y / 32);

		std::deque<const Tile* const> mapPath = Game::map.getMapPath();
		std::ptrdiff_t critter1Index = 0;
		std::ptrdiff_t critter2Index = 0;
		
		std::deque<const Tile* const>::const_reverse_iterator it = mapPath.crbegin();
		
		for(it ; it < mapPath.crend() ; ++it) {
			if((*it)->getTileX() == int(critter1posX) && (*it)->getTileY() == int(critter1posY))
				critter1Index = std::distance(mapPath.crbegin(), it);

			if((*it)->getTileX() == int(critter2posX) && (*it)->getTileY() == int(critter2posY))
				critter2Index = std::distance(mapPath.crbegin(), it);
		}
		//compares which critter is closest to the end tile
		return int(critter1Index) < int(critter2Index);
    }
};