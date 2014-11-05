#include <gameObjects/CritterFactory.h>

/**  The only method in CritterFactory, createCritter() cranks out 
  *  Critter objects based on the enum parameter. 
  */
Critter* CritterFactory::createCritter(int id, Critter::CritterType type, Waypoint* starting_waypoint) { 
  switch (type) {
    case Critter::CritterType::WHITE_CAT:
      return new WhiteCat(id, starting_waypoint);
    case Critter::CritterType::BLACK_CAT:
      return new BlackCat(id, starting_waypoint);
    default:
      return nullptr;
  }
}