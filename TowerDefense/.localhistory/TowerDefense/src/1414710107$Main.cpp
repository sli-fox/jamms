#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <SFML/Graphics.hpp>
#include <Game.h>
#include <gameStates/GameStateStart.h>

int main(int argc, char** argv[]) {
  // Create the game state manager
  Game game;

  // Add GameStates (Note: Game class handles deallocation of GameState memory)
  game.pushState(new GameStateStart(&game));
  
  // Run the game logic 
  game.gameLoop();


  /***************************** 
    Code for running unit tests 
   *****************************/
  // Get the top level suite from the registry
  CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

  // Add the test to the list of tests to run
  CppUnit::TextUi::TestRunner runner;
  runner.addTest( suite );

  // Change the default outputter to a compiler error format outputter
  runner.setOutputter( new CppUnit::CompilerOutputter( &runner.result(), std::cerr ) );

  // Run the tests
  bool wasSuccessful = runner.run();

  // Return error code 1 if the one of test failed
  return wasSuccessful ? 0 : 1;
}