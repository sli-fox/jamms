#include <test/CritterFactoryTest.h>

//Registers the fixture into the registry
CPPUNIT_TEST_SUITE_REGISTRATION( CritterFactoryTest );

void CritterFactoryTest::testCatCreation() {
  // Setup
  Waypoint waypoint1(sf::Vector2f(0,0));
  Waypoint waypoint2(sf::Vector2f(1,1));
  waypoint1.next_waypoint = &waypoint2;
  Critter* white_cat = CritterFactory::createCritter(0, Critter::CritterType::WHITE_CAT, &waypoint1);
  Critter* black_cat = CritterFactory::createCritter(1, Critter::CritterType::BLACK_CAT, &waypoint1);

  // Check
  CPPUNIT_ASSERT(white_cat->getId() == 0);
  CPPUNIT_ASSERT(black_cat->getId() == 1);
  CPPUNIT_ASSERT(white_cat->getHitPoints() != black_cat->getHitPoints());   //Check to see that the black cat has different hit points than the white cat

  // Check movement controls are instantiated properly
  CPPUNIT_ASSERT(!(white_cat->isActive));
  CPPUNIT_ASSERT(!(white_cat->hasSpawned));
  CPPUNIT_ASSERT(!(white_cat->isAtEndTile));
  CPPUNIT_ASSERT(!(white_cat->isAtNextWaypoint()));
}