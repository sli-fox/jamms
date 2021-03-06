/** @file CritterFactory.h
 *  @brief File for CritterFactory class.
 *
 *  @author Stephanie Li
 */

#pragma once
#include <gameObjects/Critter.h>
#include <gameObjects/WhiteCat.h>
#include <gameObjects/BlackCat.h>
#include <utils/Waypoint.h>

/** @brief Creates objects derived from Critter.
 *  Utility class that creates instance of a Critter subclass
 *  from a family of derived Critter classes. 
 */
class CritterFactory {
  public:

    /** @brief Factory method for Critter class.
    *   @return Critter object (subclass of Critter).
    */
    static Critter *createCritter(int id, Critter::CritterType type, Waypoint* starting_waypoint);
};