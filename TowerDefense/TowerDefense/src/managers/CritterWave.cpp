#include <managers/CritterWave.h>

/** @brief This constructor sets the type and number of critters 
 *  for the wave. 
 */
CritterWave::CritterWave(int numOfCritters, Critter::CritterType type, Waypoint* starting_waypoint) 
  : numOfCritters(numOfCritters), type(type) {

  critters_remaining = numOfCritters;

  for (int i = 0; i < this->numOfCritters; ++i) {
    this->addCritter(i, CritterFactory::createCritter(i, type, starting_waypoint));
  }

  //Set pointers for next critters
  for (int i = 0; i < this->numOfCritters - 1; ++i) {
    this->_m_critter_wave[i]->next_critter = _m_critter_wave[i+1];
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

int CritterWave::getId() const {
	return this->id;
}

int CritterWave::getCrittersRemaining() const {
	return critters_remaining;	
}

void CritterWave::setId(int id) {
	this->id = id;
}

void CritterWave::decrementCrittersRemaining() {
	--critters_remaining;
}

std::map<int, Critter*> CritterWave::getContainerOfCritters() {
  return this->_m_critter_wave;
}

void CritterWave::drawActivatedCrittersInWave(sf::RenderWindow& render_window, float delta_time) {
  for (int i = 0; i < _m_critter_wave.size(); ++i) {
   if ( _m_critter_wave[i]->isActive)
     _m_critter_wave[i]->draw(render_window, delta_time);


  }
}