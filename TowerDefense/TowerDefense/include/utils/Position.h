/** @file Position.h
 *  @brief File containing the Position class.
 *
 *  The purpose of this file is to implement a class that
 *  represents an Position in the application. 
 *
 *  @author Stephanie Li
 */

#pragma once
#include <utility>

/** @brief Represents a position in the game.
 */
class Position {
  public:

    std::pair<int, int> position;
    int x, y;

    Position(int x, int y) {
      position = std::make_pair(x, y);
      x = x;
      y = y;
    }
};