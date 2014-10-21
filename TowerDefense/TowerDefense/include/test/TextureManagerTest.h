/** @file TextureManagerTest.h
 *  @brief File containing the tests for the TextureManager class.
 *
 *  The purpose of this file is to implement a class that
 *  tests the TextureManager class. 
 *
 *  @author Stephanie Li
 */

#pragma once
#include <cppunit/extensions/HelperMacros.h>
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <managers/TextureManager.h>

/** @brief This class contains the tests for the TextureManager class.
 */
class TextureManagerTest : public CppUnit::TestFixture {
  /** Set up test suite add populate it with tests
   *  @cond Setup calls are ignored in doxygen documentation for the class*/
  CPPUNIT_TEST_SUITE( TextureManagerTest );
  CPPUNIT_TEST( testLoadTexture );
  CPPUNIT_TEST( testUnloadTexture );
  CPPUNIT_TEST_SUITE_END();
  /** @endcond */

  public:
    /** @brief Test for loadTexture() to see if a texture was
    *   correctly added to the TextureManager map.
    *   @return void.
    */
    void testLoadTexture();

    /** @brief Test for unloadTexture() to see if a texture was
    *   correctly removed to the TextureManager map.
    *   @return void.
    */
    void testUnloadTexture();
};