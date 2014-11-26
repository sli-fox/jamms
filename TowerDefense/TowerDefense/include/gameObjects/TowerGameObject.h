/** @file TowerGameObject.h
*  @brief File containing the TowerGameObject class.
*
*  The purpose of this file is to implement a class that
*  represents a displayed Tower in the application. 
*
*  @author Stephanie Li
*/

#pragma once
#include <gameObjects/GameObject.h>
#include <GameObjects/Critter.h>
#include <GameObjects/IObserver.h>
#include "Utils/TowerStrategy.h"
#include <memory>
#include <string>

/** @brief Creates a TowerGameObject.
*  TowerGameObject is a subclass of GameObject that separates 
*  GUI code specific to the Tower from the Tower model in the
*  application. 
*/
class TowerGameObject : public GameObject {
public:
  enum RateOfFire { Slow = 1, Normal, Fast };


  TowerGameObject();
  ~TowerGameObject() {};

  //Accessors
  sf::CircleShape getRangeShape() const;
  RateOfFire getRateOfFire() const;


  //Mutators
  void setRangeShape(float range);
  void setRateOfFire(RateOfFire _rate_of_fire);

  virtual bool circleToCircleIntersection(GameObject* game_object);
  bool canApplySpecialAfterEffects(Critter* critter);

protected:
  sf::CircleShape _range_shape;
  sf::Clock clock;
  sf::Time time;
  RateOfFire _rate_of_fire;

};