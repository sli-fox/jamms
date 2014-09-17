#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Game {
//Overkill to implement this class a Singleton,
//but should we do it anyway?
  public:
    static void Start();

  private:
    static bool IsExiting();
    static void GameLoop();

    enum GameState { Unintialized, ShowingSplash, Paused,
      ShowingMenu, Playing, Exiting };
    
    static GameState game_state_;
    static sf::RenderWindow main_window_;
};