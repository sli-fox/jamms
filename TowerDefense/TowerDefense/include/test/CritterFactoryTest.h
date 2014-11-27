/** @file CritterFactoryTest.h
 *  @brief File containing the tests for the CritterFactoryTest class.
 *
 *  The purpose of this file is to implement a class that
 *  tests the CritterFactory class. 
 *
 *  @author Stephanie Li
 */

#pragma once
#include <cppunit/extensions/HelperMacros.h>
#include <gameObjects/CritterFactory.h>
#include <utils/Waypoint.h>

/** @brief This class contains the tests for the CritterFactory class.
 */
class CritterFactoryTest : public CppUnit::TestFixture {
  /** Set up test suite add populate it with tests
   *  @cond Setup calls are ignored in doxygen documentation for the class*/
  CPPUNIT_TEST_SUITE( CritterFactoryTest );
  CPPUNIT_TEST( testCatCreation );
  CPPUNIT_TEST_SUITE_END();
  /** @endcond */

  public:
    /** @brief Test to see if a cat was created properly.
    *   @return void.
    */
    void testCatCreation();
};