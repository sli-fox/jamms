#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <SplashScreen.h>
#include <MainMenu.h>
#include <Pathogen.h>
#include <GameObjectManager.h>

class Game {
//Overkill to implement this class a Singleton,
//class is called only once,
//but should we do it anyway?
  public:
    static void Start();

  private:
    static bool isExiting();
    static void gameLoop();

    static void showSplashScreen();
    static void showMenu();

    enum GameState { Unintialized, ShowingSplash, Paused,
      ShowingMenu, Playing, Exiting };
    
    static GameState _game_state;
    static sf::RenderWindow _main_window;

    static GameObjectManager _game_object_manager;
};