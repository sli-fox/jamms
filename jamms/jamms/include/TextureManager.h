#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <iostream>

class TextureManager {
  public:
    static TextureManager& getInstance() {
      static TextureManager instance;
      return instance;
    }

    const sf::Texture& loadTexture(const std::string& file_name);  //Add bool smooth = true to params to enable texture smoothing
    bool unloadTexture(const std::string& file_name);

  private:
    TextureManager() {}
    ~TextureManager() {}

    TextureManager(TextureManager const&);
    void operator=(TextureManager const&);

    std::map<std::string, sf::Texture*> m_texture_map;
};
