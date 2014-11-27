/** @file TowerTest.h
 *  @brief File containing the tests for the TowerTest class.
 *
 *  The purpose of this file is to implement a class that
 *  tests the Tower class. 
 *
 *  @author Stephanie Li
 */

#pragma once
#include <cppunit/extensions/HelperMacros.h>
#include <managers/TowerManager.h>

/** @brief This class contains the tests for the Tower class.
 */
class TowerTest : public CppUnit::TestFixture {
  /** Set up test suite add populate it with tests
   *  @cond Setup calls are ignored in doxygen documentation for the class*/
  CPPUNIT_TEST_SUITE( TowerTest );
  CPPUNIT_TEST( testTowerCreation );
  CPPUNIT_TEST_SUITE_END();
  /** @endcond */

  private:
    TowerManager manager;
    Tower* small_dog;
    Tower* big_dog;

  public:
    void setUp();
    void tearDown();

    /** @brief Test to see if a Tower was created properly.
    *   @return void.
    */
    void testTowerCreation();

    void testTowerUpgrades();
};