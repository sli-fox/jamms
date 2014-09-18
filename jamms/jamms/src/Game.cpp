#include <Game.h>
#include <SplashScreen.h>

void Game::Start(void) {
  if(_game_state != Unintialized)
    return;   //Doesn't throw error because program exits

  //Game runs at fixed resolution of 1024x768
  _main_window.create(sf::VideoMode(1024, 768, 32), "Cell Defense!");
  
  _game_state = Game::ShowingSplash;

  while(!isExiting()) {
    gameLoop();
  }

  _main_window.close();
}

bool Game::isExiting() {
  if(_game_state == Game::Exiting)
    return true;
  else
    return false;
}

void Game::gameLoop() {
  sf::Event current_event;
  while(_main_window.pollEvent(current_event)) {
    switch(_game_state) {
      case Game::ShowingSplash: {
        showSplashScreen();
        break;
      }
      case Game::Playing: {
        _main_window.clear(sf::Color(0, 0, 0));
        _main_window.display();

        if(current_event.type == sf::Event::Closed) {
          _game_state = Game::Exiting;
        }
      break;
      }
    }
  }
}

void Game::showSplashScreen() {
  SplashScreen splash_screen;
  splash_screen.Show(_main_window);
  _game_state = Game::ShowingMenu;
}

Game::GameState Game::_game_state = Unintialized;
sf::RenderWindow Game::_main_window;