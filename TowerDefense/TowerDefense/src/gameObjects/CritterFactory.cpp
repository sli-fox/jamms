#include <gameObjects/CritterFactory.h>

/**  The only method in CritterFactory, createCritter() cranks out 
  *  Critter objects based on the enum parameter. 
  */
Critter* CritterFactory::createCritter(CritterType type, Waypoint* starting_waypoint) { 
  switch (type) {
    case WHITE_CAT:
      return new WhiteCat(starting_waypoint);
    case BLACK_CAT:
      return new BlackCat(starting_waypoint);
    default:
      return NULL;
  }
  if (type == WHITE_CAT)
    return new WhiteCat(starting_waypoint);
  else
    return nullptr;
}