#include <gameStates/GameStatePlay.h>

/**  The constructor sets the view to the size of the window
  *  and centers the view on the center of the window.
  */
GameStatePlay::GameStatePlay(Game* game) {
  this->game = game;
  
  // getSize() returns a sf::Vector2i object and must be cast into a sf::Vector2f
  sf::Vector2f position = sf::Vector2f(this->game->game_window.getSize());
  this->_gameView.setSize(position);
  this->_guiView.setSize(position);

  sf::Vector2f center_position = 0.5f * position;
  this->_gameView.setCenter(center_position);
  this->_guiView.setCenter(center_position);
}

/**  This function sets the view to be drawn to the window,
  *  and draws everything related to state. 
  */
void GameStatePlay::draw(const float delta_time) {
  this->game->game_window.setView(this->_gameView);
  this->game->game_window.clear(sf::Color::Black);

  //Draw map
  this->map.draw(this->game->game_window);
  
  //Draw Critter
  this->mew.draw(this->game->game_window, delta_time);

  //Set up waypoints
  sf::Vector2f v1(30.0f, 50.0f);
  sf::Vector2f v2(200.0f, 50.0f);
  sf::Vector2f v3(200.0f, 180.0f);
  sf::Vector2f v4(300.0f, 180.0f);
  sf::Vector2f v5(300.0f, 50.0f);
  sf::Vector2f v6(500.0f, 50.0f);

  std::vector<sf::Vector2f> path_points;
  path_points.push_back(v1);
  path_points.push_back(v2);
  path_points.push_back(v3);
  path_points.push_back(v4);
  path_points.push_back(v5);
  path_points.push_back(v6);

  std::vector<Waypoint> waypoints = addWaypoints(path_points);
  drawWaypoints(waypoints, this->game->game_window);
}

void GameStatePlay::update(const float delta_time) {
  this->mew.draw(this->game->game_window, delta_time);
}

void GameStatePlay::handleInput() {
  sf::Event event;

  while(this->game->game_window.pollEvent(event)) {
    switch(event.type) {
      /** Close the window */
      case sf::Event::Closed: {
        game->game_window.close();
        break;
      }
	  case sf::Event::KeyPressed: {
       sf::Vector2i localPosition = sf::Mouse::getPosition(this->game->game_window);
	   int tileX = localPosition.x/32;
	   int tileY = localPosition.y/32;
	   mapCommandLibrary(tileX, tileY, event.key.code);
	   break;
      }
      default: break;
    }
  }
}

/** @brief This function initialize waypoints while setting
 *  the next waypoints.
 */
std::vector<Waypoint> GameStatePlay::addWaypoints(std::vector<sf::Vector2f> path_points) {
  std::vector<Waypoint> waypoints;
      
  //Initialize waypoints
  for (int i = 0; i < path_points.size(); ++i) {
    Waypoint waypoint(path_points[i]);
    waypoints.push_back(waypoint);
  }
  
  //Set next waypoints
  for (int i = 0; i < waypoints.size(); ++i) {
    if (i != waypoints.size() - 1) {
      waypoints[i].next_waypoint = &waypoints[i+1];
    }
  }

  return waypoints;
}

void GameStatePlay::drawWaypoints(std::vector<Waypoint> waypoints, sf::RenderWindow& game_window) {
  for (Waypoint waypoint: waypoints) {
    waypoint.draw(game_window);
  }
}

void GameStatePlay::mapCommandLibrary(const int tileX, const int tileY, sf::Keyboard::Key thisKey){
		try{
			if(thisKey == sf::Keyboard::S){
				map.addTile("resources/images/start.png", "start", tileX, tileY);	
			}
			if(thisKey == sf::Keyboard::E){
				map.addTile("resources/images/end.png", "end", tileX, tileY);
			}
			if(thisKey == sf::Keyboard::P){
				map.addTile("resources/images/path.png", "path", tileX, tileY);
			}
			if(thisKey == sf::Keyboard::A){
				map.addTile("resources/images/scenery.png", "scenery", tileX, tileY);
			}
			if(thisKey == sf::Keyboard::D){
				map.addTile("resources/images/dead.png", "dead", tileX, tileY);
			}
			if(thisKey == sf::Keyboard::R){
				map.removeTile(tileX, tileY);
			}
			if(thisKey == sf::Keyboard::G){
				map.removeGameObject(tileX, tileY);
			}
			if(thisKey == sf::Keyboard::F){
				map.fillMap();
			}
			if(thisKey == sf::Keyboard::B){
				map.blankMap();
			}
			if(thisKey == sf::Keyboard::C){
				map.placeCritter("resources/images/critter.png", tileX, tileY);
			}
			if(thisKey == sf::Keyboard::T){
				map.placeTower("resources/images/tower.png", tileX, tileY);
			}
			if(thisKey == sf::Keyboard::L){
				map.load("testmap.xml");
			}
			if(thisKey == sf::Keyboard::K){
				map.save("testmap.xml");
			}
			if(thisKey == sf::Keyboard::V){
				if(map.isMapValid())
					cout << "map is valid: true" << endl;
				else
					cout << "map is valid: false" <<endl;
			}
		}
		catch(std::exception& e){
			cout << e.what() << endl;
		}
}

GameObjectManager GameStatePlay::_game_object_manager;
Map GameStatePlay::map(20,20);