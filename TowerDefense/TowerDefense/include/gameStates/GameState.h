/** @file GameState.h
 *  @brief File containing the GameState class.
 *
 *  The purpose of this file is to implement an interface that
 *  represents a game state in the application. 
 *
 *  @author Stephanie Li
 */

#pragma once
#include <Game.h>
#include "Button.h"

/** @brief GameState virtual base class.
 *  GameState is an interface for states within the game.
 */
class GameState {
protected:
	std::vector<std::unique_ptr<Button>> buttonList;
	Game* game;
	Button* currentButton;
  public:
    /** @brief Pointer to Game instance that handles the changing.
     *  of the states and store the info in every game state.
     */

    virtual void draw(const float delta_time) = 0;
    virtual void update(const float delta_time) = 0;
    virtual void handleInput() = 0;
};