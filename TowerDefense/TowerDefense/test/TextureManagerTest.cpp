#include <test/TextureManagerTest.h>

//Registers the fixture into the registry
CPPUNIT_TEST_SUITE_REGISTRATION( TextureManagerTest );

void TextureManagerTest::testLoadTexture() {
  // Setup
  TextureManager& _texture_manager = TextureManager::getInstance();
  sf::Sprite _sprite(_texture_manager.loadTexture("resources/images/test.png"));

  // Check
  CPPUNIT_ASSERT(_texture_manager.isPreviouslyLoaded("resources/images/test.png"));
}

void TextureManagerTest::testUnloadTexture() {
  // Setup
  TextureManager& _texture_manager = TextureManager::getInstance();
  sf::Sprite _sprite(_texture_manager.loadTexture("resources/images/test.png"));

  if (_texture_manager.isPreviouslyLoaded("resources/images/test.png")) {
    _texture_manager.unloadTexture("resources/images/test.png");
    CPPUNIT_ASSERT(_texture_manager.isPreviouslyLoaded("resources/images/test.png") == false);
  }
}