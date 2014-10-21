/** @file TextureManager.h
 *  @brief File containing the TextureManager class.
 *
 *  The purpose of this file is to implement a class that
 *  ensures each texture is loaded only once. 
 *
 *  @author Stephanie Li
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <iostream>

/** @brief Manages all the textures in the application.
 *
 *  TextureManager is a singleton class that holds the sole
 *  instance of a map of all the textures in the
 *  application. The purpose of this class is to ensure 
 *  each texture is loaded only once. 
 */
class TextureManager {
  public:
    /** @brief Returns the only instance of a TextureManager object.
     *  @return The instance of TextureManager object.
     */
    static TextureManager& getInstance() {
      static TextureManager instance;   //Guaranteed to be destroyed, instantiated on first use
      return instance;
    }

    /** @brief Returns the instance of a texture loaded by the file name.
     *  @param file_name The file name of the texture that is being loaded.
     *  @return A reference to the texture being loaded.
     */
    const sf::Texture& loadTexture(const std::string& file_name);  
    
    /** @brief Removes the instance of a texture given by the file name
     *  @param file_name The file name of the texture that is being unloaded.
     *  @return A boolean that indicates whether the texture is unloaded.
     */
    bool unloadTexture(const std::string& file_name);

    /** @brief Returns true if texture was previously loaded, false otherwise.
    *   @param file_name The file name of the texture that is being loaded.
    *   @return A boolean that indicates whether the texture was previously
    *   loaded into the TextureManager map.
    */
    const bool isPreviouslyLoaded(const std::string& file_name);  

  private:
    
    /** @brief Map of textures belonging to the class
     */
    std::map<std::string, sf::Texture*> _m_texture_map;

    /** @brief Privatized constructor for singleton implementation of the class.
     */
    TextureManager() {}

    /** @brief Privatized destructor for singleton implementation of the class.
     */
    ~TextureManager() {}

    /** @brief Overloaded constructor that is not implemented.
     */
    TextureManager(TextureManager const&);

    /** @brief Operator overload that is not implemented.
     *  @return Void.
     */
    void operator=(TextureManager const&);
};
