#include <Game.h>

void Game::Start(void) {
  if (_game_state != Unintialized)
    return;   //Doesn't throw error because program exits

  //Game runs at fixed resolution of 1024x768
  _main_window.create(sf::VideoMode(1024, 768, 32), "Cell Defense!");
  
  //Code to create pathogen sprites on screen
  //Users GameObjectManager
  for (int n=1; n<=10; ++n) {
    std::string pathogen_name = "common_cold" + std::to_string(n);
    Pathogen* pathogen = new Pathogen(Pathogen::PathogenType::CommonCold, pathogen_name);
    
    pathogen->load("resources/images/CommonCold.png");
    pathogen->setPosition(500, (300 + 40*n));

    _game_object_manager.add(pathogen_name, pathogen);
  }

  _game_state = Game::ShowingSplash;

  while (!isExiting()) {
    gameLoop();
  }

  _main_window.close();
}

bool Game::isExiting() {
  if (_game_state == Game::Exiting)
    return true;
  else
    return false;
}

void Game::gameLoop() {
  switch (_game_state) {
    case Game::ShowingMenu: {
      showMenu();
      break;
    }
    case Game::ShowingSplash: {
      showSplashScreen();
      break;
    }
    case Game::Playing: {
      sf::Event current_event;
      while (_main_window.pollEvent(current_event)) {      
        _main_window.clear(sf::Color(0, 0, 0));
        
        _game_object_manager.drawAll(_main_window);

        _main_window.display();

        if (current_event.type == sf::Event::Closed) {
          _game_state = Game::Exiting;
        }

        if (current_event.type == sf::Event::KeyPressed) {
          if (current_event.key.code == sf::Keyboard::Key::Escape) 
            showMenu(); 
        }
       }
    break;
    }
  }
}

void Game::showSplashScreen() {
  SplashScreen splash_screen;
  splash_screen.show(_main_window);
  _game_state = Game::ShowingMenu;
}

void Game::showMenu() {
  MainMenu main_menu;
  MainMenu::MenuAction action = main_menu.show(_main_window);

  switch (action) {
    case MainMenu::Exit:
      _game_state = Game::Exiting;
      break;
    case MainMenu::Play:
      _game_state = Game::Playing;
      break;
  }
}

Game::GameState Game::_game_state = Unintialized;
sf::RenderWindow Game::_main_window;
GameObjectManager Game::_game_object_manager;