#include <gameStates/GameStatePlay.h>

/**  The constructor sets the view to the size of the window
  *  and centers the view on the center of the window.
  */
GameStatePlay::GameStatePlay(Game* game) {
	this->game = game;
	//Initialize tower array with map's dimensions
	tower_manager.setArraySize(this->game->map.getMapWidth(), this->game->map.getMapHeight());
	initializeButtonMap();
	returnToMenu = false;

  this->current_waypoints = addWaypoints(getWaypointsFromMapPath());
  
  this->mew = new WhiteCat(getStartingWaypoint());
  this->blacky = new BlackCat(getStartingWaypoint());
  
  sf::Vector2f position = sf::Vector2f(this->game->game_window.getSize());
  this->_gameView.setSize(position);
  this->_guiView.setSize(position);

  sf::Vector2f center_position = 0.5f * position;
  this->_gameView.setCenter(center_position);
  this->_guiView.setCenter(center_position);
  font.loadFromFile("resources/helveticaneue-webfont.ttf");

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
  this->game->map.draw(this->game->game_window);
  drawWaypoints(this->current_waypoints, this->game->game_window);
  
  //Draw Critter
  this->mew->draw(this->game->game_window, delta_time);
  this->blacky->draw(this->game->game_window, delta_time);
   
  //Draw Towers
  this->tower_manager.draw(this->game->game_window);
  if(!tower_manager.outOfBound(tileX, tileY) && !tower_manager.isTileFree(tileX, tileY))
		this->game->game_window.draw(tower_manager.getTower(tileX,tileY)->getRangeShape());

  //Draw buttons
	for(std::map<std::string, GameObject>::iterator it = buttonMap.begin() ; it != buttonMap.end() ; ++it)
		it->second.draw(this->game->game_window);

  //Draw Money [TO BE IMPORTED INTO PLAYER CLASS]
  //For some reason, encapsulating the below code into Tower::displayWallet() to call it with
  // "this->game->game_window.draw(std::to_string(Tower::getWallet())" crashes the game...
	sf::Text text(std::to_string(Tower::getWallet()), font);
	text.setPosition(21*32, this->game->map.getMapHeight()*32);
	this->game->game_window.draw(text);
}

void GameStatePlay::update(const float delta_time) {
  this->mew->draw(this->game->game_window, delta_time);
  this->blacky->draw(this->game->game_window, delta_time);
  
  if (mew->isActive)
    moveCritter(mew, delta_time);
  
  mew->isAtEndTile = checkIfAtEndTile(mew);
  
  if (mew->isAtEndTile)
    std::cout << "Mew: I'm at the end tile!" << std::endl; 
}

void GameStatePlay::handleInput() {
	sf::Event event;

	//Checking if ANY tower on the map can attack Blacky (black cat...)
	for(int i = 0; i < this->game->map.getMapWidth(); ++i) {
		for(int j = 0; j < this->game->map.getMapHeight(); ++j) {
			if(tower_manager.getTower(i,j)->attack(blacky)) {
				std::cout << "ATTACKING!!! ";
			}
		}
	}

	while(!returnToMenu && this->game->game_window.pollEvent(event)) {
		localPosition = sf::Mouse::getPosition(this->game->game_window);
		tileX = localPosition.x/32;
		tileY = localPosition.y/32;

		switch(event.type) {
			/** Close the window */
		case sf::Event::Closed: {
			game->game_window.close();
			break;
								}
		case sf::Event::MouseButtonPressed: {
			buttonCommandLibrary();
			towerCommandLibrary(tileX, tileY);
			break;
											}
		case sf::Event::MouseMoved: {

			break;

									}
		case sf::Event::KeyPressed: {
			blacky->controlCat(event.key.code);	// for controlling blackcat
			//mew->controlCat(event.key.code);
			towerCommandLibrary(tileX, tileY);
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
  deque<const Tile* const> path_tiles = this->game->map.getMapPath();

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

bool GameStatePlay::checkIfAtEndTile(Critter* critter) {
  if (int(critter->getPosition().x) == this->current_waypoints[current_waypoints.size() - 1].position.x 
   && int(critter->getPosition().y) == this->current_waypoints[current_waypoints.size() - 1].position.y) 
    return true;
  else
    return false;
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

void GameStatePlay::towerCommandLibrary(const int tileX, const int tileY){
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		if(this->game->map.getTile(tileX, tileY) != nullptr && this->game->map.getTile(tileX, tileY)->spriteContains(localPosition)
			&& this->game->map.getTile(tileX, tileY)->getType() == Tile::TYPE::SCENERY)
			tower_manager.buyTower(towerSelector, tileX, tileY);
	}
	else if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
		if(this->game->map.getTile(tileX, tileY) != nullptr && this->game->map.getTile(tileX, tileY)->spriteContains(localPosition) 
			&& this->game->map.getTile(tileX, tileY)->getType() == Tile::TYPE::SCENERY){
				tower_manager.sellTower(tileX, tileY);
		}
	}		
	/*if(this->game->map.getTile(tileX, tileY) != nullptr && this->game->map.getTile(tileX, tileY)->getType() == Tile::TYPE::SCENERY) {
	if(thisKey == sf::Keyboard::Num1){
	tower_manager.buyTower(Tower::TowerType::ShihTzu, tileX, tileY);	
	}
	if(thisKey == sf::Keyboard::Num2){
	tower_manager.buyTower(Tower::TowerType::Dalmatian, tileX, tileY);
	}
	if(thisKey == sf::Keyboard::Num3){
	tower_manager.buyTower(Tower::TowerType::Bulldog, tileX, tileY);
	}
	*/
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::U) && !tower_manager.isTileFree(tileX, tileY)){
		tower_manager.getTower(tileX, tileY)->upgradeTower();
	}
	/*
	if(thisKey == sf::Keyboard::BackSpace){
	tower_manager.sellTower(tileX, tileY);
	}
	*/
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::M)){
		tower_manager.displayTowerArray();
	}
}

void GameStatePlay::buttonCommandLibrary(){
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		if(buttonMap["returnToEditorBtn"].spriteContains(localPosition)){
			returnToMenu = true;
			this->game->popState();
		}
		else if(buttonMap["pauseBtn"].spriteContains(localPosition)){
			//do something
		}
		else if(buttonMap["unpauseBtn"].spriteContains(localPosition)){
			//do something
		}
		else if(buttonMap["bulldog_0_Btn"].spriteContains(localPosition)){
			towerSelector = Tower::Bulldog;
		}
		else if(buttonMap["dalmatian_0_Btn"].spriteContains(localPosition)){
			towerSelector = Tower::Dalmatian;
		}
		else if(buttonMap["shihtzu_0_Btn"].spriteContains(localPosition)){
			towerSelector = Tower::ShihTzu;
		}
	}
}

void GameStatePlay::initializeButtonMap(){
	string imagePath = "resources/images/";
	string towerPath = "resources/images/towers/";
	string squaresPath = "resources/images/towers/squares";

	GameObject displayCurrentWave;
	displayCurrentWave.load(imagePath + "CritterDisplayBox.png");
	displayCurrentWave.setPosition(0*32,12*32);
	buttonMap.emplace("displayCurrentWave", displayCurrentWave);

	GameObject displayNextWave;
	displayNextWave.load(imagePath + "CritterDisplayBox.png");
	displayNextWave.setPosition(0*32,17*32);
	buttonMap.emplace("displayNextWave", displayNextWave);

	GameObject towerDisplayBox;
	towerDisplayBox.load(imagePath + "CritterDisplayBox.png");
	towerDisplayBox.setPosition(24*32,14*32);
	buttonMap.emplace("towerDisplayBox", towerDisplayBox);

	GameObject pauseBtn;
	pauseBtn.load(imagePath + "PauseBtn.png");
	pauseBtn.setPosition(0*32,22*32);
	buttonMap.emplace("pauseBtn", pauseBtn);

	GameObject unpauseBtn;
	unpauseBtn.load(imagePath + "UnpauseBtn.png");
	unpauseBtn.setPosition(2*32,22*32);
	buttonMap.emplace("unpauseBtn", unpauseBtn);

	GameObject returnToEditorBtn;
	returnToEditorBtn.load(imagePath + "ReturnToEditorBtn.png");
	returnToEditorBtn.setPosition(4*32,22*32);
	buttonMap.emplace("returnToEditorBtn", returnToEditorBtn);

	GameObject bulldog_0_Btn;
	bulldog_0_Btn.load(towerPath + "bulldog_0.png");
	bulldog_0_Btn.setPosition(24*32,12*32);
	buttonMap.emplace("bulldog_0_Btn", bulldog_0_Btn);

	GameObject bulldog_1_Btn;
	bulldog_1_Btn.load(towerPath + "bulldog_1.png");
	bulldog_1_Btn.setPosition(25*32,12*32);
	buttonMap.emplace("bulldog_1_Btn", bulldog_1_Btn);

	GameObject bulldog_2_Btn;
	bulldog_2_Btn.load(towerPath + "bulldog_2.png");
	bulldog_2_Btn.setPosition(26*32,12*32);
	buttonMap.emplace("bulldog_2_Btn", bulldog_2_Btn);

	GameObject dalmatian_0_Btn;
	dalmatian_0_Btn.load(towerPath + "dalmatian_0.png");
	dalmatian_0_Btn.setPosition(27*32,12*32);
	buttonMap.emplace("dalmatian_0_Btn", dalmatian_0_Btn);

	GameObject dalmatian_1_Btn;
	dalmatian_1_Btn.load(towerPath + "dalmatian_1.png");
	dalmatian_1_Btn.setPosition(28*32,12*32);
	buttonMap.emplace("dalmatian_1_Btn", dalmatian_1_Btn);

	GameObject dalmatian_2_Btn;
	dalmatian_2_Btn.load(towerPath + "dalmatian_2.png");
	dalmatian_2_Btn.setPosition(29*32,12*32);
	buttonMap.emplace("dalmatian_2_Btn", dalmatian_2_Btn);

	GameObject shihtzu_0_Btn;
	shihtzu_0_Btn.load(towerPath + "shihtzu_0.png");
	shihtzu_0_Btn.setPosition(24*32,13*32);
	buttonMap.emplace("shihtzu_0_Btn", shihtzu_0_Btn);

	GameObject shihtzu_1_Btn;
	shihtzu_1_Btn.load(towerPath + "shihtzu_1.png");
	shihtzu_1_Btn.setPosition(25*32,13*32);
	buttonMap.emplace("shihtzu_1_Btn", shihtzu_1_Btn);

	GameObject shihtzu_2_Btn;
	shihtzu_2_Btn.load(towerPath + "shihtzu_2.png");
	shihtzu_2_Btn.setPosition(26*32,13*32);
	buttonMap.emplace("shihtzu_2_Btn", shihtzu_2_Btn);

}

GameObjectManager GameStatePlay::_game_object_manager;
TowerManager& GameStatePlay::tower_manager = TowerManager::getInstance();
