#include <views/MainMenu.h>

MainMenu::MenuAction MainMenu::show(sf::RenderWindow& window) {
  TextureManager& t_manager = TextureManager::getInstance();
  sf::Sprite main_menu_sprite(t_manager.loadTexture("resources/images/MainMenuScreen.png"));

  //Setup clickable regions 
  MenuItem play_button;
  play_button.rect.left = 0;
  play_button.rect.top = 185;
  play_button.rect.width = 1024;
  play_button.rect.height = 200;
  play_button.action = PLAY;

  MenuItem exit_button;
  exit_button.rect.left = 0;
  exit_button.rect.top = 385;
  exit_button.rect.width = 1024;
  exit_button.rect.height = 200;
  exit_button.action = EXIT;

  _menu_items.push_back(play_button);
  _menu_items.push_back(exit_button);

  window.draw(main_menu_sprite);
  window.display();

  return getMenuResponse(window);
}

Menu::MenuAction MainMenu::getMenuResponse(sf::RenderWindow& window) {
  sf::Event menu_event;

  while (true) {
    while (window.pollEvent(menu_event)) {
      if(menu_event.type == sf::Event::MouseButtonPressed) {
        return handleClick(menu_event.mouseButton.x, menu_event.mouseButton.y);
      }
      if (menu_event.type == sf::Event::Closed) {
        return EXIT;
      }
    }
  }
}