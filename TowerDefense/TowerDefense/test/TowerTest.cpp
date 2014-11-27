#include <test/TowerTest.h>

//Registers the fixture into the registry
CPPUNIT_TEST_SUITE_REGISTRATION( TowerTest );

void TowerTest::setUp() {
  small_dog = manager.buyTower("BabyShihTzu", 0, 0);
  big_dog = manager.buyTower("BabyBulldog", 1, 1);
}

void TowerTest::tearDown() {
  delete small_dog;
  delete big_dog;
}

void TowerTest::testTowerCreation() {
  CPPUNIT_ASSERT(small_dog->getType() != big_dog->getType());
}

void TowerTest::testTowerUpgrades() {
  int old_power_small_dog = small_dog->getPower();
  int old_power_big_dog = big_dog->getPower();
  manager.upgradeTower(0,0);
  manager.upgradeTower(1,1);
  CPPUNIT_ASSERT(small_dog->getPower() != old_power_small_dog);
  CPPUNIT_ASSERT(big_dog->getPower() != old_power_big_dog);
}