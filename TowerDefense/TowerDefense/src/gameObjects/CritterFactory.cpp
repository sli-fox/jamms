#include <gameObjects/CritterFactory.h>

/**  The only method in CritterFactory, createCritter() cranks out 
  *  Critter objects based on the enum parameter. 
  */
Critter* CritterFactory::createCritter(CritterType type) {
  if (type == WHITE_CAT)
    return new WhiteCat;
  else
    return nullptr;
}