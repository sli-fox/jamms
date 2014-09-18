#include <SplashScreen.h>
#include <TextureManager.h>

void SplashScreen::Show(sf::RenderWindow& render_window) {
/*  sf::Texture texture;
  if(texture.loadFromFile("resources/images/SplashScreen.png") != true)
    return;   //Should throw error 
*/
  TextureManager& t_manager = TextureManager::getInstance();
  sf::Sprite splash_screen_sprite(t_manager.loadTexture("resources/images/SplashScreen.png"));

  render_window.draw(splash_screen_sprite);
  render_window.display();

  sf::Event event;
  while(true) {
    while(render_window.pollEvent(event)) {
      if(event.type == sf::Event::EventType::KeyPressed
        || event.type == sf::Event::EventType::MouseButtonPressed
        || event.type == sf::Event::EventType::Closed) {
        return;
      }
    }
  }
}