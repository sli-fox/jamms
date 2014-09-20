#include <SplashScreen.h>

void SplashScreen::show(sf::RenderWindow& render_window) {
  TextureManager& t_manager = TextureManager::getInstance();
  sf::Sprite splash_screen_sprite(t_manager.loadTexture("resources/images/SplashScreen.png"));

  render_window.draw(splash_screen_sprite);
  render_window.display();

  sf::Event event;
  while (true) {
    while (render_window.pollEvent(event)) {
      if (event.type == sf::Event::EventType::KeyPressed
        || event.type == sf::Event::EventType::MouseButtonPressed
        || event.type == sf::Event::EventType::Closed) {
        return;
      }
    }
  }
}