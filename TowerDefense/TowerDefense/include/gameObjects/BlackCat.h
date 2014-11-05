/** @file BlackCat.h
 *  @brief Representation of BlackCat object.
 *
 *  This is the representation of the BlackCat object.
 *
 *  @author Stephanie Li
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <gameObjects/Critter.h>
#include <utils/Animation.h>
#include <utils/Waypoint.h>

class GameStatePlay;  //Allows class to know about GameStatePlay

/** @brief Class for BlackCat.
 *  Subclass of Critter. 
 */
class BlackCat : public Critter {
  public:
   
	BlackCat() {}
    BlackCat(int id, Waypoint* starting_waypoint);
    ~BlackCat() {}

	void controlCat(sf::Keyboard::Key arrowKey);
    
  private:
    /** @brief Initialization function for a BlackCat.
     *  @param animations Array of specified animations
     *  @return Void.
     */
    virtual void initializeCritter(const std::vector<Animation>& animations);
};