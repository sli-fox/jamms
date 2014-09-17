sf::Texture texture;
  if(texture.loadFromFile("resources/images/SplashScreen.png") != true)
    return;   //Should throw error 

  sf::Sprite sprite;
  sprite.setTexture(texture);