#include <gameStates/GameStatePlay.h>

/**  The constructor sets the view to the size of the window
  *  and centers the view on the center of the window.
  */
GameStatePlay::GameStatePlay(Game* game) {
  //Load the test map
  map.load("testmap.xml");

	//Initialize tower array with map's dimensions
	tower_manager.setArraySize(map.getMapWidth(), map.getMapHeight());

  this->current_waypoints = addWaypoints(getWaypointsFromMapPath());
  
  this->mew = new WhiteCat(getStartingWaypoint());
  this->blacky = new BlackCat(getStartingWaypoint());
  this->game = game;
  
  sf::Vector2f position = sf::Vector2f(this->game->game_window.getSize());
  this->_gameView.setSize(position);
  this->_guiView.setSize(position);

  sf::Vector2f center_position = 0.5f * position;
  this->_gameView.setCenter(center_position);
  this->_guiView.setCenter(center_position);

  // Activate mew!
  mew->isActive = true;
}

/**  This function sets the view to be drawn to the window,
  *  and draws everything related to state. 
  */
void GameStatePlay::draw(const float delta_time) {
  this->game->game_window.setView(this->_gameView);
  this->game->game_window.clear(sf::Color::Black);

  //Draw map
  this->map.draw(this->game->game_window);
  drawWaypoints(this->current_waypoints, this->game->game_window);
  
  //Draw Critter
  this->mew->draw(this->game->game_window, delta_time);
  this->blacky->draw(this->game->game_window, delta_time);
   
  //Draw Towers
  this->tower_manager.draw(this->game->game_window);
  if(!tower_manager.outOfBound(tileX, tileY) && !tower_manager.isTileFree(tileX, tileY))
		this->game->game_window.draw(tower_manager.getTower(tileX,tileY)->getRangeShape());

  //Draw Money [TO BE IMPORTED INTO PLAYER CLASS]
  //For some reason, encapsulating the below code into Tower::displayWallet() to call it with
  // "this->game->game_window.draw(std::to_string(Tower::getWallet())" crashes the game...
	sf::Font font;
	font.loadFromFile("resources/helveticaneue-webfont.ttf");
	sf::Text text(std::to_string(Tower::getWallet()), font);
	text.setPosition(0, map.getMapHeight()*32);
	this->game->game_window.draw(text);

}

void GameStatePlay::update(const float delta_time) {
  this->mew->draw(this->game->game_window, delta_time);
  this->blacky->draw(this->game->game_window, delta_time);
  
  if (mew->isActive)
    moveCritter(mew, delta_time);

}



void GameStatePlay::handleInput() {
  sf::Event event;
  	localPosition = sf::Mouse::getPosition(this->game->game_window);
	tileX = localPosition.x/32;
	tileY = localPosition.y/32;
	
	//Checking if ANY tower on the map can attack Blacky (black cat...)
	for(int i = 0; i < map.getMapWidth(); ++i) {
		for(int j = 0; j < map.getMapHeight(); ++j) {
			if(tower_manager.getTower(i,j)->attack(blacky)) {
				std::cout << "ATTACKING!!! ";
			}
		}
	}

  while(this->game->game_window.pollEvent(event)) {

    switch(event.type) {
      /** Close the window */
      case sf::Event::Closed: {
        game->game_window.close();
        break;
      }
	  case sf::Event::KeyPressed: {
	   blacky->controlCat(event.key.code);	// for controlling blackcat
	   //mew->controlCat(event.key.code);
	   mapCommandLibrary(tileX, tileY, event.key.code);
	   towerCommandLibrary(tileX, tileY, event.key.code);
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
    if (i == waypoints.size() - 1){
      waypoints[i].next_waypoint = NULL;
    }
  }

  return waypoints;
}

std::vector<sf::Vector2f> GameStatePlay::getWaypointsFromMapPath() {
  std::vector<sf::Vector2f> waypoint_positions;
  deque<const Tile* const> path_tiles = this->map.getMapPath();

  // Add starting waypoint position
  waypoint_positions.push_back(sf::Vector2f(path_tiles[0]->getTileX()*32 + 16, path_tiles[0]->getTileY()*32 + 16));
  
  // Any path with a direction change must have at least 4 tiles
  if (path_tiles.size() > 3) {
    // Set current tile
    const Tile* current_tile = path_tiles[0];

    for (int i = 0; i < path_tiles.size() - 1; ++i) {
      if (i + 3 == path_tiles.size() - 1)   // No change of direction can happen in less than 4 tiles
        break;

      int next_x = path_tiles[i+1]->getTileX();
      int next_y = path_tiles[i+1]->getTileY();

      if (current_tile->getTileX() == next_x) {   // Path is vertical
        // Check if the tile after the next tile changes direction
        if (next_x != path_tiles[i+2]->getTileX()) {
          waypoint_positions.push_back(sf::Vector2f(path_tiles[i+1]->getTileX()*32 + 16, path_tiles[i+1]->getTileY()*32 + 16));
        }
        current_tile = path_tiles[i+1];
      } 
      else if (current_tile->getTileY() == next_y) { // Path is horizontal
        // Check if the tile after the next tile changes direction
        if (next_y != path_tiles[i+2]->getTileY()) {
          waypoint_positions.push_back(sf::Vector2f(path_tiles[i+1]->getTileX()*32 + 16, path_tiles[i+1]->getTileY()*32 + 16));
        }
        current_tile = path_tiles[i+1];
      }
    }
  }
  // Add last waypoint position
  waypoint_positions.push_back(sf::Vector2f(path_tiles[path_tiles.size() - 1]->getTileX()*32 + 16, path_tiles[path_tiles.size() - 1]->getTileY()*32 + 16));
  return waypoint_positions;
}

void GameStatePlay::drawWaypoints(std::vector<Waypoint> waypoints, sf::RenderWindow& game_window) {
  for (Waypoint waypoint: waypoints) {
    waypoint.draw(game_window);
  }
}

void GameStatePlay::moveCritter(Critter* critter, const float delta_time) {
 if (!critter->isAtNextWaypoint()) {
   switch (critter->getMovementDirection()) {
      case Critter::MovementDirection::RIGHT:
        critter->updatePosition(critter->getSpeed()*delta_time, 0);
        break;
      case Critter::MovementDirection::LEFT:
        critter->updatePosition(-(critter->getSpeed()*delta_time), 0);
        break;
      case Critter::MovementDirection::UP:
        critter->updatePosition(0, -(critter->getSpeed()*delta_time));
        break;
      case Critter::MovementDirection::DOWN:
        critter->updatePosition(0, critter->getSpeed()*delta_time);
        break;
    }
  } else {
    if (critter->getCurrentWaypoint()->next_waypoint->next_waypoint) {
        critter->setCurrentWaypoint(critter->getCurrentWaypoint()->next_waypoint);
       
        Critter::MovementDirection direction = critter->getMovementDirection();
        critter->setAnimationIndex(direction);
       }
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

void GameStatePlay::towerCommandLibrary(const int tileX, const int tileY, sf::Keyboard::Key thisKey){
	if(!tower_manager.outOfBound(tileX, tileY) && map.getTile(tileX, tileY)->getType() == Tile::TYPE::SCENERY) {
		if(thisKey == sf::Keyboard::Num1){
			tower_manager.buyTower(Tower::TowerType::ShihTzu, tileX, tileY);	
		}
		if(thisKey == sf::Keyboard::Num2){
			tower_manager.buyTower(Tower::TowerType::Dalmatian, tileX, tileY);
		}
		if(thisKey == sf::Keyboard::Num3){
			tower_manager.buyTower(Tower::TowerType::Bulldog, tileX, tileY);
		}
		if(thisKey == sf::Keyboard::U && !tower_manager.isTileFree(tileX, tileY)){
			tower_manager.getTower(tileX, tileY)->upgradeTower();
		}
		if(thisKey == sf::Keyboard::BackSpace){
			tower_manager.sellTower(tileX, tileY);
		}
		if(thisKey == sf::Keyboard::M){
			tower_manager.displayTowerArray();
		}
	}
}


GameObjectManager GameStatePlay::_game_object_manager;
Map GameStatePlay::map(20,20);
TowerManager& GameStatePlay::tower_manager = TowerManager::getInstance();
