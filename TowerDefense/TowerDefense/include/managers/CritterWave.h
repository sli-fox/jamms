/** @file CritterWave.h
 *  @brief File for CritterWave class.
 *
 *  @author Stephanie Li
 */

#pragma once
#include <gameObjects/Critter.h>
#include <gameObjects/CritterFactory.h>
#include <map>
#include <algorithm>

/** @brief Represents a wave of Critters.
 *  Class that has holds Critters in a map data structure, which
 *  represents a wave of Critters 
 */
class CritterWave {
  public:
    /** @brief Map representing a critter wave.
     */
    const int numOfCritters;
    
    /** @brief Type of critter in a critter wave.
     */
    Critter::CritterType type;

    /** @brief Pointer to the next CritterWave.
     */
    CritterWave* next_wave;

    CritterWave(int numOfCritters, Critter::CritterType type, Waypoint* starting_waypoint);
    ~CritterWave();

    /** @brief Overloaded cout operator to print out CritterWaves.
     *  @param output Output stream address
     *  @param critter Const address to CritterWave
     *  @return Address to output stream
     */
    friend std::ostream& operator<<(std::ostream& output, const CritterWave& critter_wave) {
      typedef std::map<int, Critter*>::const_iterator it_type;
      for (it_type iterator = critter_wave._m_critter_wave.begin(); iterator != critter_wave._m_critter_wave.end(); ++iterator) {
        output << "\tCritter id: " << iterator->first << std::endl;      }
      return output;
    }

    /** @brief Returns a reference to a Critter in the map.
     *  @param critter_id Id of the Critter to be found
     *  @return Pointer to a Critter in the map.
     */
    Critter* findCritter(int id) const;

    /** @brief Adding a Critter to the wave.
     */
    void addCritter(int id, Critter* critter);

    /** @brief Remove a critter from the CritterWave map.
     *  @param critter_id Id of the Critter to be removed
     */
    void removeCritter(int id);

    /** @brief Returns how many critters are in a CritterWave map.
     *  @return Count of number of Critters in a wave.
     */
    int getCritterCount() const;

    std::map<int, Critter*> getContainerOfCritters();

    void drawActivatedCrittersInWave(sf::RenderWindow& render_window, float delta_time); 
  private:
    /** @brief Map representing a critter wave.
     */
    std::map<int, Critter*> _m_critter_wave;

    /** @brief Struct deallocating resources used in a CritterWave map
     */
    struct CritterWaveDeallocator {
      /** @brief Overloading of the function operator ()
       *  @param item Coupled values that represents an item in the map
       *  @return Void.
       */
      void operator()(const std::pair<int, Critter*>& item) {
        delete item.second;   // Delete the map pair's value (Critter*) 
      }
    };
};