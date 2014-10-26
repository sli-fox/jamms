#include <managers/TextureManager.h>

/**  loadTexture() looks for the given file name string 
  *  in the map of textures shared across the application. If the 
  *  file name is found, that means the texture has been previously
  *  loaded and the function returns a reference to the texture. If
  *  the file name is not found, the texture is loaded, added to the
  *  map of textures and a reference to it is returned.
  *  Note: Adding 'bool smooth = true' as a parameter enables texture 
  *  smoothing.
  */
const sf::Texture& TextureManager::loadTexture(const std::string& file_name) {
  std::map<std::string, sf::Texture*>::const_iterator texture_search_iterator = _m_texture_map.find(file_name);

  if (texture_search_iterator != _m_texture_map.end())
    return *texture_search_iterator->second;
  
  sf::Texture* texture = new sf::Texture;  
  if (!texture->loadFromFile(file_name)) {
    std::cout << "Error: unable to load image " + file_name;
  } 
    _m_texture_map.insert(std::map<std::string, sf::Texture*>::value_type (file_name, texture));
    return *_m_texture_map[file_name];
}

/**  loadTexture() looks for the given file name string 
  *  in the map of textures shared across the application. If the 
  *  file name is found, the texture reference is removed from the map
  *  and the function returns true. If the file name is not found or 
  *  can't be removed, the function returns false. 
  */
bool TextureManager::unloadTexture(const std::string& file_name) {
  std::map<std::string, sf::Texture*>::const_iterator texture_search_iterator = _m_texture_map.find(file_name);

  if (texture_search_iterator != _m_texture_map.end()) {
    delete texture_search_iterator->second;
    _m_texture_map.erase(texture_search_iterator);
    return true;
  } else {
    return false;
  }
}


/**  isPreviouslyLoaded() looks for the given file name 
  *  in the map of textures shared across the application. If the 
  *  file name is found, that means the texture has been previously
  *  loaded and the function returns true. If the texture has not 
  *  previously loaded, it returns false.
  */
const bool TextureManager::isPreviouslyLoaded(const std::string& file_name) {
  std::map<std::string, sf::Texture*>::const_iterator texture_search_iterator = _m_texture_map.find(file_name);

  if (texture_search_iterator != _m_texture_map.end()) {
    return true;
  } else {
    return false;
  }
}
