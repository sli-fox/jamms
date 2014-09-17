#include "stdafx.h"
#include "Game.h"

void Game::Start(void) {
  if(game_state_ != Unintialized)
    return;   //Doesn't throw error because program exits

  main_window_.create(sf::VideoMode(1024, 768, 32), "Cell Defense!");
  game_state_ = Game::Playing;

  while(!IsExiting()) {
    GameLoop();
  }

  main_window_.close();
}

bool Game::IsExiting() {
  if(game_state_ == Game::Exiting)
    return true;
  else
    return false;
}

void Game::GameLoop() {
  sf::Event current_event;
  while(main_window_.pollEvent(current_event)) {
    switch(game_state_) {
      case Game::Playing: {
        main_window_.clear(sf::Color(0, 0, 0));
        main_window_.display();

        if(current_event.type == sf::Event::Closed) {
          game_state_ = Game::Exiting;
        }
      break;
      }
    }
  }
}

Game::GameState Game::game_state_ = Unintialized;
sf::RenderWindow Game::main_window_;