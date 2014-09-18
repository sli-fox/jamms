#include <TextureManager.h>

const sf::Texture& TextureManager::loadTexture(const std::string& file_name) {
  std::map<std::string, sf::Texture*>::const_iterator texture_search_iterator = m_texture_map.find(file_name);
  
  if(texture_search_iterator != m_texture_map.end())
    return *texture_search_iterator->second;
  
  sf::Texture* texture = new sf::Texture;  
  if(!texture->loadFromFile(file_name)) {
    std::cout << "Error: unable to load image " + file_name;
  }

  m_texture_map.insert(std::map<std::string, sf::Texture*>::value_type (file_name, texture));
  return *m_texture_map[file_name];
}

std::map<std::string, sf::Texture*> m_texture_map;