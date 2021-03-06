/** @file WhiteCat.h
 *  @brief Representation of WhiteCat object.
 *
 *  This is the representation of the WhiteCat object.
 *
 *  @author Stephanie Li
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <gameObjects/Critter.h>
#include <utils/Animation.h>
#include <utils/Waypoint.h>

class GameStatePlay;  //Allows class to know about GameStatePlay

/** @brief Class for WhiteCat.
 *  Subclass of Critter. 
 */
class WhiteCat : public Critter {
  public:
       
    WhiteCat(int id, Waypoint* starting_waypoint);
    ~WhiteCat() {}
    
  private:
    /** @brief Initialization function for a WhiteCat.
     *  @param animations Array of specified animations
     *  @return Void.
     */
    virtual void initializeCritter(const std::vector<Animation>& animations);
};