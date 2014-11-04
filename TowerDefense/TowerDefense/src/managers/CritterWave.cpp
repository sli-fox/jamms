#include <managers/CritterWave.h>

/** @brief This constructor sets the type and number of critters 
 *  for the wave. 
 */
CritterWave::CritterWave(int numOfCritters, CritterFactory::CritterType type) 
  : numOfCritters(numOfCritters), type(type) {

  for (int i = 1; i <= this->numOfCritters; ++i) {
    this->addCritter(i, CritterFactory::createCritter(type));
  }

}


/**  @brief This destructor iterates through the map, calling a deallocator which deletes
  *  Critter* references in a wave.
  */
CritterWave::~CritterWave() {
  for_each(_m_critter_wave.begin(), _m_critter_wave.end(), CritterWaveDeallocator());
}

void CritterWave::addCritter(int id, Critter* critter) {
  _m_critter_wave.insert(std::pair<int, Critter*>(id, critter));
}

/** Iterate through the map, looking for the given Critter id, 
 *  if found, delete the pointer and remove the Critter* from the map. 
 */
void CritterWave::removeCritter(int id) {
  std::map<int, Critter*>::iterator results = _m_critter_wave.find(id);
  if (results != _m_critter_wave.end()) {
    delete results->second;
    _m_critter_wave.erase(results);
  }
}

/** Iterate through the map, looking for the given Critter id. 
 *  If end of map is reached, return null, else return the Critter*. 
 */
Critter* CritterWave::findCritter(int id) const {
  std::map<int, Critter*>::const_iterator results = _m_critter_wave.find(id);
  if (results == _m_critter_wave.end()) 
    return NULL;
  return results->second;
}

int CritterWave::getCritterCount() const {
  return _m_critter_wave.size();
}
