#pragma once
#include "stdafx.h"

class Game {
//Overkill to implement this class a Singleton,
//but should we do it anyway?
  public:
    static void Start();

  private:
    static bool IsExiting();
    static void GameLoop();

    static void ShowSplashScreen();

    enum GameState { Unintialized, ShowingSplash, Paused,
      ShowingMenu, Playing, Exiting };
    
    static GameState game_state_;
    static sf::RenderWindow main_window_;
};