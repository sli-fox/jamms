#include <managers/GameObjectManager.h>

GameObjectManager::~GameObjectManager() {
  std::for_each(_m_game_objects.begin(), _m_game_objects.end(), GameObjectDeallocator());
}

void GameObjectManager::add(std::string name, GameObject* game_object) {
  _m_game_objects.insert(std::pair<std::string, GameObject*>(name, game_object));
}

void GameObjectManager::remove(std::string name) {
  std::map<std::string, GameObject*>::iterator results = _m_game_objects.find(name);
  if (results != _m_game_objects.end()) {
    delete results->second;
    _m_game_objects.erase(results);
  }
}

GameObject* GameObjectManager::getGameObject(std::string name) const {
  std::map<std::string, GameObject*>::const_iterator results = _m_game_objects.find(name);
  if (results == _m_game_objects.end()) 
    return NULL;
  return results->second;
}

int GameObjectManager::getObjectCount() const {
  return _m_game_objects.size();
}

void GameObjectManager::drawAll(sf::RenderWindow& render_window) {
  std::map<std::string, GameObject*>::const_iterator itr = _m_game_objects.begin();
  while(itr != _m_game_objects.end()) {
    itr->second->draw(render_window);
    itr++;
  }
}