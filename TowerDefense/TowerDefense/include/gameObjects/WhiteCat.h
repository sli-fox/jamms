/** @file WhiteCat.h
 *  @brief Representation of WhiteCat object.
 *
 *  This is the representation of the WhiteCat object.
 *
 *  @author Stephanie Li
 */

#pragma once
#include <gameObjects/Critter.h>
#include <utils/animation.h>

/** @brief Class for WhiteCat.
 *  Subclass of Critter. 
 */
class WhiteCat : public Critter {
  public:

    WhiteCat();
    ~WhiteCat() {};

    /** @brief Update changes in the WhiteCat.
      */
    virtual void update();
    
  private:
    /** @brief Initialization function for a WhiteCat.
     *  @param animations Array of specified animations
     *  @return Void.
     */
    virtual void initializeCritter(const std::vector<Animation>& animations);
};