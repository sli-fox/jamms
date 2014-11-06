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
  this->show_waypoints = false;

  //Set up critter wave levels
  this->setCritterWaveLevels(getStartingWaypoint());

  //Set current wave to the first level
  this->current_wave = wave_levels[0];

  //Set last activated critter to the first critter in the wave and activate it
  this->delay_count = 0;
  this->last_activated_critter = current_wave->findCritter(0);
  last_activated_critter->isActive = true;

  this->mew = new WhiteCat(11, getStartingWaypoint());
  this->blacky = new BlackCat(12, getStartingWaypoint());
  showBlacky = false;

  
  sf::Vector2f position = sf::Vector2f(this->game->game_window.getSize());
  this->_gameView.setSize(position);
  this->_guiView.setSize(position);

  sf::Vector2f center_position = 0.5f * position;
  this->_gameView.setCenter(center_position);
  this->_guiView.setCenter(center_position);
  font.loadFromFile("resources/helveticaneue-webfont.ttf");
  mapBackdrop.load("resources/images/MapBackdrop.png");
  mapBackdrop.setPosition(0*32,0*32);

  // Activate mew!
  //mew->isActive = true;
}

/**  This function sets the view to be drawn to the window,
  *  and draws everything related to state. 
  */
void GameStatePlay::draw(const float delta_time) {
  this->game->game_window.setView(this->_gameView);
  this->game->game_window.clear(sf::Color::Black);

  //Draw map
  mapBackdrop.draw(this->game->game_window);
  this->game->map.draw(this->game->game_window);

  if (show_waypoints)
    drawWaypoints(this->current_waypoints, this->game->game_window);

  //Draw Critter
  //this->mew->draw(this->game->game_window, delta_time);
  if (showBlacky)
	  this->blacky->draw(this->game->game_window, delta_time);

  //Draw Critter wave
  this->current_wave->drawActivatedCrittersInWave(this->game->game_window, delta_time);

  //Draw Towers
  this->tower_manager.draw(this->game->game_window);
  if(!tower_manager.outOfBound(tileX, tileY) && !tower_manager.isTileFree(tileX, tileY))
		this->game->game_window.draw(tower_manager.getTower(tileX,tileY)->getRangeShape());

  //Draw buttons
	for(std::map<std::string, GameObject>::iterator it = buttonMap.begin() ; it != buttonMap.end() ; ++it)
		it->second.draw(this->game->game_window);

  //Draw Specs of Towers, Critters and Player
	if(tower_manager.getTower(tileX, tileY) != NULL && tower_manager.getTower(tileX, tileY)->spriteContains(localPosition)){
		towerSpecs.setString(tower_manager.getTower(tileX, tileY)->getTowerSpecs());
		this->game->game_window.draw(towerSpecs);
	}
	critterSpecs.setString("CURRENT WAVE: \n" + blacky->getCritterSpecs());
	this->game->game_window.draw(critterSpecs);
	playerSpecs.setString(Game::player.getPlayerSpecs());
	this->game->game_window.draw(playerSpecs);
}

void GameStatePlay::update(const float delta_time) {
  //Draw  & move activated Critters within a wave
  this->current_wave->drawActivatedCrittersInWave(this->game->game_window, delta_time);
  moveActivatedCritters(delta_time);

  //Activate Critters within a wave based on number of update cycles
  if (delay_count >= 175 && last_activated_critter->next_critter) {
    last_activated_critter->next_critter->isActive = true;
    std::cout << "ACTIVATE critter with id " << last_activated_critter->next_critter->getId() << std::endl;
    last_activated_critter = last_activated_critter->next_critter;
    delay_count = 0;
  } 
  delay_count += 1;

  //Handle the removal of critters from the current wave
  handleCritterRemovalFromWave();

  //Handle level switching
  handleCritterWaveLevelSwitching();

  //this->mew->draw(this->game->game_window, delta_time);
 
	this->blacky->draw(this->game->game_window, delta_time);
  
  //if (mew->isActive)
    //moveCritter(mew, delta_time);
  
  //mew->isAtEndTile = checkIfAtEndTile(mew);
  
  //if (mew->isAtEndTile)
    //std::cout << "Mew: I'm at the end tile!" << std::endl; 
}

void GameStatePlay::setCritterWaveLevels(Waypoint* starting_waypoint) {
  CritterWave* wave1 = new CritterWave(5, Critter::CritterType::WHITE_CAT, getStartingWaypoint());
  CritterWave* wave2 = new CritterWave(5, Critter::CritterType::BLACK_CAT, getStartingWaypoint());
  CritterWave* wave3 = new CritterWave(10, Critter::CritterType::WHITE_CAT, getStartingWaypoint());
  CritterWave* wave4 = new CritterWave(10, Critter::CritterType::BLACK_CAT, getStartingWaypoint());

  this->wave_levels.push_back(wave1);
  this->wave_levels.push_back(wave2);
  this->wave_levels.push_back(wave3);  
  this->wave_levels.push_back(wave4);

  for (int i = 0; i < wave_levels.size() - 1; ++i) {
    wave_levels[i]->next_wave = wave_levels[i+1];
	std::cout << wave_levels[i]->getCritterCount() << std::cout;
  }

}


void GameStatePlay::handleInput() {
	sf::Event event;

	//Checking if ANY tower on the map can attack Blacky (black cat...)
	for(int i = 0; i < this->game->map.getMapWidth(); ++i) {
		for(int j = 0; j < this->game->map.getMapHeight(); ++j) {
			if(tower_manager.getTower(i,j)->canAttack(blacky)) {
				tower_manager.getTower(i,j)->attack();
			}
		}
	}
	GameStatePlay::registerObservers();



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
			case sf::Event::KeyPressed: {
				towerCommandLibrary(tileX, tileY);
				if(event.key.code == sf::Keyboard::B)
					(!showBlacky) ? showBlacky = true : showBlacky = false;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
					(!show_waypoints) ? show_waypoints = true : show_waypoints = false;
				blacky->controlCat(event.key.code);	// for controlling blackcat
				break;
			}
			default: break;
		}
	}
}

// Attach every tower to every active critter
void GameStatePlay::registerObserver() {
  std::map<int, Critter*> critters = current_wave->getContainerOfCritters();
  	for(int i = 0; i < this->game->map.getMapWidth(); ++i) {
		for(int j = 0; j < this->game->map.getMapHeight(); ++j) {
			if(tower_manager.getTower(i,j) != NULL) {
				for (int i = 0; i < critters.size(); ++i) {
					if(critters[i]->isActive) {
						critters[i]->attach(tower_manager.getTower(i,j));
						critters[i]->notify();
					}
				}
			}
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
      if (i + 2 == path_tiles.size() - 1)   // No change of direction can happen in less than 4 tiles
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

void GameStatePlay::moveActivatedCritters(const float delta_time) {
  std::map<int, Critter*> critters = current_wave->getContainerOfCritters();
  for (int i = 0; i < critters.size(); ++i) {
    if (critters[i]->isActive)
      moveCritter(critters[i], delta_time);
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

void GameStatePlay::handleCritterRemovalFromWave() {
  std::map<int, Critter*> critters = current_wave->getContainerOfCritters();
  for (int i = 0; i < critters.size(); ++i) {
    //Check if critters are at end tile
    critters[i]->isAtEndTile = checkIfAtEndTile(critters[i]);
    
    if (critters[i]->isAtEndTile && critters[i]->isActive) {
      //Take a life from the player
      this->game->player.loseLives(1);
      //Remove points from player
      this->game->player.losePoints(critters[i]->getStealPointsStrength());
    }

    if (critters[i]->isAtEndTile) {
      current_wave->findCritter(i)->isActive = false;
    }
  }
}

void GameStatePlay::handleCritterWaveLevelSwitching() {
  std::map<int, Critter*> critters = current_wave->getContainerOfCritters();
  for (int i = 0; i < critters.size(); ++i) {
    if (critters[i]->isActive)
      return;
  }
  if (current_wave->next_wave) {
    current_wave = current_wave->next_wave;
    this->delay_count = 0;
    this->last_activated_critter = current_wave->findCritter(0);
    last_activated_critter->isActive = true;
  }
}

Waypoint* GameStatePlay::getStartingWaypoint() {
  return &current_waypoints[0];
}

CritterWave* GameStatePlay::getCurrentCritterWave(){
  return current_wave;
}


void GameStatePlay::towerCommandLibrary(const int tileX, const int tileY){
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		if(tower_manager.getTower(tileX, tileY) == nullptr && this->game->map.getTile(tileX, tileY) != nullptr
			&& this->game->map.getTile(tileX, tileY)->getType() == Tile::TYPE::SCENERY)
			tower_manager.buyTower(towerSelector, tileX, tileY);
	}
	else if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
		if(tower_manager.getTower(tileX, tileY) != nullptr && tower_manager.getTower(tileX, tileY)->spriteContains(localPosition)){
				tower_manager.sellTower(tileX, tileY);
		}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::U) && !tower_manager.isTileFree(tileX, tileY)){
		tower_manager.getTower(tileX, tileY)->upgradeTower();
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)){
		tower_manager.clearAllTowers();
	}
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
		else if(buttonMap["nextWaveBtn"].spriteContains(localPosition)){
			//steph place function here
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
	displayCurrentWave.load(imagePath + "DisplayBox.png");
	displayCurrentWave.setPosition(0*32,12*32);
	buttonMap.emplace("displayCurrentWave", displayCurrentWave);
	critterSpecs.setFont(font);
	critterSpecs.setPosition(0*32+8,12*32);
	critterSpecs.setColor(sf::Color::Black);
	critterSpecs.setCharacterSize(13);

	GameObject displayNextWave;
	displayNextWave.load(imagePath + "DisplayBox.png");
	displayNextWave.setPosition(0*32,17*32);
	buttonMap.emplace("displayNextWave", displayNextWave);

	GameObject towerDisplayBox;
	towerDisplayBox.load(imagePath + "DisplayBox.png");
	towerDisplayBox.setPosition(24*32,14*32);
	buttonMap.emplace("towerDisplayBox", towerDisplayBox);
	towerSpecs.setFont(font);
	towerSpecs.setPosition(24*32+8,14*32);
	towerSpecs.setColor(sf::Color::Black);
	towerSpecs.setCharacterSize(13);
	
	GameObject playerDisplayBox;
	playerDisplayBox.load(imagePath + "DisplayBox.png");
	playerDisplayBox.setPosition(9*32,12*32);
	buttonMap.emplace("playerDisplayBox", playerDisplayBox);
	playerSpecs.setFont(font);
	playerSpecs.setPosition(9*32+8,12*32);
	playerSpecs.setColor(sf::Color::Black);
	playerSpecs.setCharacterSize(13);

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

	GameObject nextWaveBtn;
	nextWaveBtn.load(imagePath + "NextWaveBtn.png");
	nextWaveBtn.setPosition(6*32,22*32);
	buttonMap.emplace("nextWaveBtn", nextWaveBtn);

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
