#include <MainMenu.h>

MainMenu::MenuItemAction MainMenu::Show(sf::RenderWindow& window) {
  TextureManager& t_manager = TextureManager::getInstance();
  sf::Sprite main_menu_sprite(t_manager.loadTexture("resources/images/MainMenuScreen.png"));
}