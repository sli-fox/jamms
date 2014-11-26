#include <gameStates/GameStatePlay.h>

/**  The constructor sets the view to the size of the window
  *  and centers the view on the center of the window.
  */
GameStatePlay::GameStatePlay(Game* game) {
  this->game = game;

	initializeButtonMap();
  firstStart = true;
	returnToMenu = false;
  endOfWaves = false;

  this->current_waypoints = addWaypoints(getWaypointsFromMapPath());
  this->show_waypoints = false;

  //Set up critter wave levels
  this->setCritterWaveLevels(getStartingWaypoint());

  //Set current wave to the first level
  this->current_wave = wave_levels[0];

  //Set last activated critter to the first critter in the wave and activate it
  this->delay_count = 0;
  this->last_activated_critter = current_wave->findCritter(0);

  this->mew = new WhiteCat(11, getStartingWaypoint());
  this->blacky = new BlackCat(12, getStartingWaypoint());

  
  sf::Vector2f position = sf::Vector2f(this->game->game_window.getSize());
  //JEREMY LOOK HERE FOR VIEWS
  // Link to more info: http://sfml-dev.org/tutorials/2.0/graphics-view.php
  // You can do split screen and just keep the view camera unmoving
  this->_gameView.setSize(position);
  this->_guiView.setSize(position);

  sf::Vector2f center_position = 0.5f * position;
  this->_gameView.setCenter(center_position);
  this->_guiView.setCenter(center_position);
  font.loadFromFile("resources/helveticaneue-webfont.ttf");

  mapBackdrop.load("resources/images/MapBackdrop.png");
  mapBackdrop.setPosition(0*32,0*32);

  interfaceBackdrop.load("resources/images/InterfaceBackdrop.png");
  interfaceBackdrop.setPosition(0*32,12*32);

  // Activate mew!
  //mew->isActive = true;
}

void GameStatePlay::runThreads() {
  drawThread = std::thread(&GameStatePlay::draw, this, game->delta_time);

        if (drawThread.joinable())
        drawThread.join();
}

/**  This function sets the view to be drawn to the window,
  *  and draws everything related to state. 
  */
void GameStatePlay::draw(const float delta_time) {  
  //sf::Context context;

  this->game->game_window.setView(this->_gameView);
  this->game->game_window.clear(sf::Color::Black);

  //Draw map
  mapBackdrop.draw(this->game->game_window);
  this->game->map.draw(this->game->game_window);

  if (show_waypoints)
    drawWaypoints(this->current_waypoints, this->game->game_window);

  //Draw Critter
  //this->mew->draw(this->game->game_window, delta_time);
  if (blacky->isActive)
	  this->blacky->draw(this->game->game_window, delta_time);

  //Draw Critter wave
  this->current_wave->drawActivatedCrittersInWave(this->game->game_window, delta_time);
  this->tower_manager.draw(this->game->game_window);

  if(tower_manager.getTower(tileX, tileY) != nullptr) {
	  this->game->game_window.draw(tower_manager.getTower(tileX,tileY)->getRangeShape());
    }

  //Draw backdrop for interface
  interfaceBackdrop.draw(this->game->game_window);

    //Draw buttons
	for(std::map<std::string, GameObject>::iterator it = buttonMap.begin() ; it != buttonMap.end() ; ++it)
		it->second.draw(this->game->game_window);

  //Draw Specs of Critters and Player
	this->game->game_window.draw(waveSpecs);
	this->game->game_window.draw(nextWaveSpecs);
	playerSpecs.setString(Game::player.getPlayerSpecs());
	this->game->game_window.draw(playerSpecs);
	//this->game->game_window.draw(towerSpecs);
	//Draw Towers and their Specs

	if(buttonMap["BabyShihTzu_Btn"].spriteContains(localPosition)) {
	  towerSpecs.setString(getTower1ButtonSpecs());
	  this->game->game_window.draw(towerSpecs);
	  //this->game->game_window.draw(upgradeTowerSpecs);
    }else if(buttonMap["BabyDalmatian_Btn"].spriteContains(localPosition)) {
	  towerSpecs.setString(getTower2ButtonSpecs());
	  this->game->game_window.draw(towerSpecs);
	  //this->game->game_window.draw(upgradeTowerSpecs);
    }else if(buttonMap["BabyBulldog_Btn"].spriteContains(localPosition)) {
	  towerSpecs.setString(getTower3ButtonSpecs());
	  this->game->game_window.draw(towerSpecs);
	  //this->game->game_window.draw(upgradeTowerSpecs);
    }
	else if(buttonMap["pauseBtn"].spriteContains(localPosition)) {
	  buttonSpecs.setString(getPauseButtonSpecs());
	  this->game->game_window.draw(buttonSpecs);
	  //this->game->game_window.draw(upgradeTowerSpecs);
    }
	else if(buttonMap["unpauseBtn"].spriteContains(localPosition)) {
	  buttonSpecs.setString(getUnPauseButtonSpecs());
	  this->game->game_window.draw(buttonSpecs);
	  //this->game->game_window.draw(upgradeTowerSpecs);
    }
	else if(buttonMap["returnToEditorBtn"].spriteContains(localPosition)) {
	  buttonSpecs.setString(getReturnToEditorButtonSpecs());
	  this->game->game_window.draw(buttonSpecs);
	  //this->game->game_window.draw(upgradeTowerSpecs);
    }
	else if(buttonMap["startWaveBtn"].spriteContains(localPosition)) {
	  buttonSpecs.setString(getStartWaveButtonSpecs());
	  this->game->game_window.draw(buttonSpecs);
	  //this->game->game_window.draw(upgradeTowerSpecs);
    }
	 for (int i = 0; i < this->current_wave->getContainerOfCritters().size(); ++i) 
	 {
		if ( this->current_wave->getContainerOfCritters()[i]->isActive )
			if( this->current_wave->getContainerOfCritters()[i]->spriteContains(localPosition) )
			{
				critterSpecs.setString(this->current_wave->getContainerOfCritters()[i]->getCritterSpecs());
				this->game->game_window.draw(critterSpecs);

			}
	}


    if(tower_manager.getTower(tileX, tileY) != nullptr) {
	  towerSpecs.setString(tower_manager.getTower(tileX, tileY)->getTowerSpecs());
	  //upgradeTowerSpecs.setString(tower_manager.getTower(tileX, tileY)->getUpgradeTowerSpecs());
	  this->game->game_window.draw(towerSpecs);
	  //this->game->game_window.draw(upgradeTowerSpecs);
    }
	if(!critterHealth.empty() && !healthClock.empty()){
		for(int i = 0 ; i < critterHealth.size() ; ++i){
			healthTime = healthClock[i].getElapsedTime();
			if(healthTime.asSeconds() > 0.5 )
				critterHealth[i].setString("");
			this->game->game_window.draw(critterHealth[i]);
		}
	}
}

void GameStatePlay::update(const float delta_time) {
  handleGameOver();

 
  //Draw  & move activated Critters within a wave
  this->current_wave->drawActivatedCrittersInWave(this->game->game_window, delta_time);
  moveActivatedCritters(delta_time);
  waveSpecs.setString("CURRENT WAVE ("
	  + std::to_string(current_wave->getId()+1) + "/"
	  + std::to_string(wave_levels.size()) + "):\n"
	  + "Number of cats left: " 
	  + std::to_string(current_wave->getCrittersRemaining()) + "/"
	  + std::to_string(current_wave->getContainerOfCritters().size()) + "\n"
	  + current_wave->findCritter(current_wave->getContainerOfCritters().size()-1)->getCritterSpecs());

  if(current_wave->next_wave != nullptr) {
	  nextWaveSpecs.setString("NEXT WAVE ("
		  + std::to_string(current_wave->getId()+2) + "/"
		  + std::to_string(wave_levels.size()) + "):\n"+ "Number of cats: "
		  + std::to_string(current_wave->next_wave->getContainerOfCritters().size()) + "\n"
		  + current_wave->next_wave->findCritter(0)->getCritterSpecs());
  } else {
	  nextWaveSpecs.setString("No more waves!");
  }

  //Activate Critters within a wave based on number of update cycles
  if (last_activated_critter->hasSpawned) {
    if (delay_count >= 175 && last_activated_critter->next_critter) {
      last_activated_critter->next_critter->hasSpawned = true;
      last_activated_critter->next_critter->isActive = true;
      std::cout << green << "ACTIVATE critter with id " << last_activated_critter->next_critter->getId() << std::endl;
      last_activated_critter = last_activated_critter->next_critter;
      delay_count = 0;
    }
    delay_count += 1;
  }

  //Handle the removal of critters from the current wave
  handleCritterRemovalFromWave();

 if (blacky->isActive)
	  this->blacky->draw(this->game->game_window, delta_time);
  
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

  for (int i = 0; i < wave_levels.size(); ++i) {
	  wave_levels[i]->setId(i);
    if (i < wave_levels.size() - 1)
      wave_levels[i]->next_wave = wave_levels[i+1];
  }
}

void GameStatePlay::handleInput() {
	sf::Event event;

	std::map<int, Critter*> critters = current_wave->getContainerOfCritters();
	for(std::map<std::pair<int,int>, Tower*>::iterator it = tower_manager.getTowerMap()->begin() ; it != tower_manager.getTowerMap()->end() ; ++it) {

		Tower* tower = it->second;
		if(tower != NULL) {

			for (int i = 0; i < critters.size(); ++i) {
				while(critters[i]->isActive && tower->canAttack(critters[i]) && !this->game->isGamePaused) {
					tower->attack();
					Critter* target = tower->getTarget();
					if(target != NULL) {
						std::pair<float, float> tpos = target->getPosition();
						sf::Text ch(std::to_string(target->getHitPoints()), font, 12); 
						ch.setPosition(tpos.first, tpos.second - 18);
						ch.setColor(sf::Color::Red);
						critterHealth[target->getId()] = ch;
						sf::Clock c;
						healthClock[target->getId()] = c;
					}

					if(!critters[i]->getSpecialEffectApplied()) {
						tower->applySpecialEffect(critters[i]);
						critters[i]->setSpecialEffectApplied(true);
					}
				}
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
    case sf::Event::LostFocus: {
			if (!this->game->isGamePaused)
        this->game->isGamePaused = true;
      break;
    }
    case sf::Event::GainedFocus: {
      std::cout << "Game Gained Focus" << std::endl;
			if (this->game->isGamePaused)
        this->game->isGamePaused = false;
      break;
    }
		case sf::Event::MouseButtonPressed: {
			buttonCommandLibrary();
			towerCommandLibrary(tileX, tileY);
			break;
		}
		case sf::Event::MouseMoved: {
			if(tower_manager.getTower(tileX, tileY) != NULL && tower_manager.getTower(tileX, tileY)->spriteContains(localPosition)) {
				towerSpecs.setString(tower_manager.getTower(tileX, tileY)->getTowerSpecs());
				//upgradeTowerSpecs.setString(tower_manager.getTower(tileX, tileY)->getUpgradeTowerSpecs());
			}
      break;
    }
		case sf::Event::KeyPressed: {
			towerCommandLibrary(tileX, tileY);
			blacky->controlCat(event.key.code);	// for controlling blackcat
			if(event.key.code == sf::Keyboard::B)
				(!blacky->isActive) ? blacky->isActive = true : blacky->isActive = false;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				(!show_waypoints) ? show_waypoints = true : show_waypoints = false;
				//show_waypoints = !show_waypoints;
			break;
		}
		default: break;
		}
	}
}

// Attach ONE tower to every active critter
void GameStatePlay::registerObserver(Tower* tower) {
	std::map<int, Critter*> critters = current_wave->getContainerOfCritters();
	for (int i = 0; i < critters.size(); ++i) {
		if(critters[i]->isActive) {
			critters[i]->attach(tower);
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
  
  // Any path with a direction change must have at least 3 tiles
  if (path_tiles.size() > 2) {
    // Set current tile
    const Tile* current_tile = path_tiles[0];

    for (int i = 0; i < path_tiles.size() - 1; ++i) {
      if (i + 2 == path_tiles.size())   // No change of direction can happen in less than 3 tiles
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
  if (int(critter->getPosition().first) == this->current_waypoints[current_waypoints.size() - 1].position.x 
   && int(critter->getPosition().second) == this->current_waypoints[current_waypoints.size() - 1].position.y) 
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

		//handle removal of dead critters
		if(critters[i]->isActive && critters[i]->getHitPoints() <= 0){
			std::cout << red << "Cat " << critters[i]->getId() << " fled away!" << std::endl;
			Game::player.earnCash(critters[i]->getPlayerReward() * 2);
			Game::player.gainPoints(critters[i]->getPlayerReward() * 3);

			current_wave->decrementCrittersRemaining();
			critters[i]->isActive = false;
		}
		//handle removal of critters at end tile
		else if (critters[i]->isActive && critters[i]->isAtEndTile) {
			//Take a life from the player
			this->game->player.loseLives(1);
			//Remove points from player
			this->game->player.losePoints(critters[i]->getStealPointsStrength());
			current_wave->decrementCrittersRemaining();
			critters[i]->isActive = false;
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
    last_activated_critter->hasSpawned = true;
  }
}

Waypoint* GameStatePlay::getStartingWaypoint() {
  return &current_waypoints[0];
}

CritterWave* GameStatePlay::getCurrentCritterWave(){
  return current_wave;
}

void GameStatePlay::handleGameOver() {
  std::map<int, Critter*> critters = current_wave->getContainerOfCritters();
  if (current_wave == wave_levels[wave_levels.size() - 1]) {
    if (critters[critters.size() - 1]->hasSpawned && !critters[critters.size() - 1]->isActive)
      endOfWaves = true;
  }
  if (this->game->player.getLives() <= 0)
    this->game->pushState(new GameStateGameOver(this->game));
  if (endOfWaves)
    this->game->pushState(new GameStateWin(this->game));
}

void GameStatePlay::towerCommandLibrary(const int tileX, const int tileY){
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		if(tower_manager.getTower(tileX, tileY) == nullptr && this->game->map.getTile(tileX, tileY) != nullptr
			&& this->game->map.getTile(tileX, tileY)->getType() == Tile::TYPE::SCENERY) {
			tower_manager.buyTower(towerSelector, tileX, tileY);
			if(tower_manager.getTower(tileX, tileY) != nullptr) {
				registerObserver(tower_manager.getTower(tileX, tileY));
			}
		}
	}
	else if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
		if(tower_manager.getTower(tileX, tileY) != nullptr && tower_manager.getTower(tileX, tileY)->spriteContains(localPosition)){
				tower_manager.sellTower(tileX, tileY);
		}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::U) && tower_manager.getTower(tileX, tileY) != NULL) {
		tower_manager.upgradeTower(tower_manager.getTower(tileX, tileY));
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)){
		tower_manager.clearAllTowers();
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::T)){
			for (map<pair<int,int>, Tower*>::iterator it = tower_manager.getTowerMap()->begin() ; it != tower_manager.getTowerMap()->end() ; ++it) {
				if(it->second != nullptr)
					std::cout << white << "=> " << it->second->getName() << '\n';
			}
	}
}

void GameStatePlay::buttonCommandLibrary() {
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if(buttonMap["returnToEditorBtn"].spriteContains(localPosition)) {
			returnToMenu = true;
			tower_manager.clearAllTowers();
			game->player.resetStats();
			this->game->popState();
		}
		else if(buttonMap["startWaveBtn"].spriteContains(localPosition)) {
      if (firstStart) {
        last_activated_critter->hasSpawned = true;
        last_activated_critter->isActive = true;
        firstStart = false;
      }
      handleCritterWaveLevelSwitching();
		}
		else if(buttonMap["pauseBtn"].spriteContains(localPosition)) {
			if (!this->game->isGamePaused)
        this->game->isGamePaused = true;
		}
		else if(buttonMap["unpauseBtn"].spriteContains(localPosition)){
			if (this->game->isGamePaused)
        this->game->isGamePaused = false;
		}

		else if(buttonMap["BabyShihTzu_Btn"].spriteContains(localPosition)) {
			towerSelector = "BabyShihTzu";
		}
		else if(buttonMap["BabyDalmatian_Btn"].spriteContains(localPosition)) {
			towerSelector = "BabyDalmatian";
		}
		else if(buttonMap["BabyBulldog_Btn"].spriteContains(localPosition)) {
			towerSelector = "BabyBulldog";
		}
	}
}

void GameStatePlay::initializeButtonMap() {
	string imagePath = "resources/images/";
	string towerPath = "resources/images/towers/";
	string squaresPath = "resources/images/towers/squares";

	GameObject displayCurrentWave;
	displayCurrentWave.load(imagePath + "DisplayBox.png");
	displayCurrentWave.setPosition(0*32,12*32);
	buttonMap.emplace("displayCurrentWave", displayCurrentWave);
	waveSpecs.setFont(font);
	waveSpecs.setPosition(0*32+8,12*32);
	waveSpecs.setColor(sf::Color::Black);
	waveSpecs.setCharacterSize(13);

	GameObject displayNextWave;
	displayNextWave.load(imagePath + "DisplayBox.png");
	displayNextWave.setPosition(0*32,17*32);
	buttonMap.emplace("displayNextWave", displayNextWave);
	nextWaveSpecs.setFont(font);
	nextWaveSpecs.setPosition(0*32+8,17*32);
	nextWaveSpecs.setColor(sf::Color::Black);
	nextWaveSpecs.setCharacterSize(13);

	GameObject displayStartWave;
	displayStartWave.load(imagePath + "DisplayBox.png");
	displayStartWave.setPosition(0*32,17*32);
	buttonMap.emplace("displayStartWave", displayStartWave);

	//GameObject towerDisplayBox;
	//towerDisplayBox.load(imagePath + "DisplayBox.png");
	//towerDisplayBox.setPosition(24*32,14*32);
	//buttonMap.emplace("towerDisplayBox", towerDisplayBox);
	towerSpecs.setFont(font);
	towerSpecs.setPosition(24*32+8,14*32);
	towerSpecs.setColor(sf::Color::White);
	towerSpecs.setCharacterSize(13);

	critterSpecs.setFont(font);
	critterSpecs.setPosition(24*32+8,14*32);
	critterSpecs.setColor(sf::Color::White);
	critterSpecs.setCharacterSize(13);

	buttonSpecs.setFont(font);
	buttonSpecs.setPosition(24*32+8,14*32);
	buttonSpecs.setColor(sf::Color::White);
	buttonSpecs.setCharacterSize(13);


	/*
	GameObject upgradeTowerDisplayBox;
	upgradeTowerDisplayBox.load(imagePath + "DisplayBox.png");
	upgradeTowerDisplayBox.setPosition(24*32,19*32);
	buttonMap.emplace("upgradeTowerDisplayBox", upgradeTowerDisplayBox);
	upgradeTowerSpecs.setFont(font);
	upgradeTowerSpecs.setPosition(24*32+8,19*32);
	upgradeTowerSpecs.setColor(sf::Color::Black);
	upgradeTowerSpecs.setCharacterSize(13);
	*/
	
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

	GameObject startWaveBtn;
	startWaveBtn.load(imagePath + "StartWaveBtn.png");
	startWaveBtn.setPosition(6*32,22*32);
	buttonMap.emplace("startWaveBtn", startWaveBtn);
	
	GameObject BabyShihTzu_Btn;
	BabyShihTzu_Btn.load(towerPath + "ShihTzu_0.png");
	BabyShihTzu_Btn.setPosition(24*32,12*32);
	buttonMap.emplace("BabyShihTzu_Btn", BabyShihTzu_Btn);
	
	GameObject BabyDalmatian_Btn;
	BabyDalmatian_Btn.load(towerPath + "Dalmatian_0.png");
	BabyDalmatian_Btn.setPosition(25*32,12*32);
	buttonMap.emplace("BabyDalmatian_Btn", BabyDalmatian_Btn);

	GameObject BabyBulldog_Btn;
	BabyBulldog_Btn.load(towerPath + "Bulldog_0.png");
	BabyBulldog_Btn.setPosition(26*32,12*32);
	buttonMap.emplace("BabyBulldog_Btn", BabyBulldog_Btn);

	/*
	GameObject bulldog_1_Btn;
	bulldog_1_Btn.load(towerPath + "bulldog_1.png");
	bulldog_1_Btn.setPosition(25*32,12*32);
	buttonMap.emplace("bulldog_1_Btn", bulldog_1_Btn);

	GameObject bulldog_2_Btn;
	bulldog_2_Btn.load(towerPath + "bulldog_2.png");
	bulldog_2_Btn.setPosition(26*32,12*32);
	buttonMap.emplace("bulldog_2_Btn", bulldog_2_Btn);
	*/

/*<<<<<<< HEAD
	GameObject dalmatian_0_Btn;
	dalmatian_0_Btn.load(towerPath + "tower.png");
	dalmatian_0_Btn.setPosition(25*32,12*32);
	buttonMap.emplace("dalmatian_0_Btn", dalmatian_0_Btn);
	
=======
>>>>>>> b7247c7a6abd342519a4767bc5d6217d38734434 */
	/*
	GameObject dalmatian_1_Btn;
	dalmatian_1_Btn.load(towerPath + "dalmatian_1.png");
	dalmatian_1_Btn.setPosition(28*32,12*32);
	buttonMap.emplace("dalmatian_1_Btn", dalmatian_1_Btn);

	GameObject dalmatian_2_Btn;
	dalmatian_2_Btn.load(towerPath + "dalmatian_2.png");
	dalmatian_2_Btn.setPosition(29*32,12*32);
	buttonMap.emplace("dalmatian_2_Btn", dalmatian_2_Btn);
	*/

/*<<<<<<< HEAD
	GameObject shihtzu_0_Btn;
	shihtzu_0_Btn.load(towerPath + "icetower.png");
	shihtzu_0_Btn.setPosition(26*32,12*32);
	buttonMap.emplace("shihtzu_0_Btn", shihtzu_0_Btn);

=======
>>>>>>> b7247c7a6abd342519a4767bc5d6217d38734434 */
	/*
	GameObject shihtzu_1_Btn;
	shihtzu_1_Btn.load(towerPath + "shihtzu_1.png");
	shihtzu_1_Btn.setPosition(25*32,13*32);
	buttonMap.emplace("shihtzu_1_Btn", shihtzu_1_Btn);

	GameObject shihtzu_2_Btn;
	shihtzu_2_Btn.load(towerPath + "shihtzu_2.png");
	shihtzu_2_Btn.setPosition(26*32,13*32);
	buttonMap.emplace("shihtzu_2_Btn", shihtzu_2_Btn);
	*/

}

std::string GameStatePlay::getTower1ButtonSpecs() {
	std::stringstream output;
	output << "CURRENT TOWER SPECIFICATIONS:" << std::endl;
	output << "Name: " << "Concrete  "<< std::endl;
	output << "Upgrade: 0"<< std::endl;
	output << "Power: 1"<< std::endl;
	output << "Range:  1.5" << std::endl;
	output << "Fire Rate: Slow"  << std::endl;
	output << "Buy Cost: 70 coins" << std::endl;
	output << "Upgrade Cost: 20 coins" << std::endl;
	output << "Sell Cost: 30 coins" << std::endl;
	output << "Special Effect: None" << std::endl;

	return output.str();
}


std::string GameStatePlay::getTower2ButtonSpecs() {
	std::stringstream output;
	output << "CURRENT TOWER SPECIFICATIONS:" << std::endl;
	output << "Name: " << "Concrete_2  "<< std::endl;
	output << "Upgrade: 0"<< std::endl;
	output << "Power: 2"<< std::endl;
	output << "Range:  3" << std::endl;
	output << "Fire Rate: Medium"  << std::endl;
	output << "Buy Cost: 140 coins" << std::endl;
	output << "Upgrade Cost: 20 coins" << std::endl;
	output << "Sell Cost: 30 coins" << std::endl;
	output << "Special Effect: None" << std::endl;

	return output.str();
}

std::string GameStatePlay::getTower3ButtonSpecs() {
	std::stringstream output;
	output << "CURRENT TOWER SPECIFICATIONS:" << std::endl;
	output << "Name: " << "Concrete_3 "<< std::endl;
	output << "Upgrade: 0"<< std::endl;
	output << "Power: 3"<< std::endl;
	output << "Range:  4.5" << std::endl;
	output << "Fire Rate: Fast"  << std::endl;
	output << "Buy Cost: 210 coins" << std::endl;
	output << "Upgrade Cost: 60 coins" << std::endl;
	output << "Sell Cost: 30 coins" << std::endl;
	output << "Special Effect: None" << std::endl;

	return output.str();
}

std::string GameStatePlay::getPauseButtonSpecs() {
	std::stringstream output;
	output << "Button is used to pause the game." << std::endl;
	output << "Critters in the range of tower "<< std::endl;
	output << "wont be affected." << std::endl;

	return output.str();
}

std::string GameStatePlay::getUnPauseButtonSpecs() {
	std::stringstream output;
	output << "Button is used to unpause the game." << std::endl;

	return output.str();
}
std::string GameStatePlay::getReturnToEditorButtonSpecs() {
	std::stringstream output;
	output << "Brings the game back to Map Editor." << std::endl;
	output << "Towers placed in the game are cleared up." << std::endl;
	output << "Waves are also cleared." << std::endl;

	return output.str();
}
std::string GameStatePlay::getStartWaveButtonSpecs() {
	std::stringstream output;
	output << "Start the wave of Critters." << std::endl;
	
	return output.str();
}
GameObjectManager GameStatePlay::_game_object_manager;
TowerManager& GameStatePlay::tower_manager = TowerManager::getInstance();
