#include "stdafx.h"
#include "SplashScreen.h"

void SplashScreen::Show(sf::RenderWindow & render_window) {
  sf::Texture texture;
  if(texture.loadFromFile("resources/images/SplashScreen.png") != true)
    return;   //Should throw error 

  sf::Sprite sprite;
  sprite.setTexture(texture);   //Should we have a helper class that loads textures
                                //and creates Sprites?

  render_window.draw(sprite);
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