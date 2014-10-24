/** @file Waypoint.h
 *  @brief File containing the Waypoint class.
 *
 *  The purpose of this file is to implement a class that
 *  creates waypoints for Critter movement.  
 *
 *  @author Stephanie Li
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <Game.h>

/** @brief Represents an Waypoint in the game.
 */
class Waypoint {
  public:
    /** @brief Position of the Waypoint.
     */
    sf::Vector2f position;

    /** @brief Pointer to the next Waypoint.
     */
    Waypoint* next_waypoint;

    /** @brief Pointer to Game instance.
     */
    Game* game;

    /** @brief Waypoint constructor
     */
    Waypoint(sf::Vector2f position) : position(position) {}
    ~Waypoint() {}

    /** @brief Draws the Waypoint -- for testing purposes only 
     */
    void draw(); 
};