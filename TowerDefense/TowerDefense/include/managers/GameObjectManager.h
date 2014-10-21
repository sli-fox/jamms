#pragma once
#include <gameObjects/GameObject.h>

class GameObjectManager {
  public:
    GameObjectManager() {}
    ~GameObjectManager();

    void add(std::string name, GameObject* game_object);
    //addVectorContents function
    void remove(std::string name);
    int getObjectCount() const;
    GameObject* getGameObject(std::string name) const;

    void drawAll(sf::RenderWindow& render_window);

  private:
    std::map<std::string, GameObject*> _m_game_objects;

    //This is a functor, which overloads the function operator ()
    struct GameObjectDeallocator {
      void operator()(const std::pair<std::string, GameObject*>& p) const {
        delete p.second;
      }
    };
};