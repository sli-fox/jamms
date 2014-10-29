#include <gameStates/GameStateEditor.h>

/**  The constructor sets the view to the size of the window
  *  and centers the view on the center of the window.
  */
GameStateEditor::GameStateEditor(Game* game) {
  this->game = game;
  // getSize() returns a sf::Vector2i object and must be cast into a sf::Vector2f
  sf::Vector2f position = sf::Vector2f(this->game->game_window.getSize());
  this->_editorView.setSize(position);
  this->_editorView.setSize(position);

  sf::Vector2f center_position = 0.5f * position;
  this->_editorView.setCenter(center_position);
  this->_editorView.setCenter(center_position);

  initializeInterface();
  shownText.setPosition(2*32.f,15*32.f);
  shownText.setString("Please enter a name for the map: ");
  shownText.setFont(game->font);
  shownText.setCharacterSize(12);
  testText.setPosition(8*32.f,15*32.f);
  testText.setString("map name here");
  testText.setFont(game->font);
  testText.setCharacterSize(12);

}

/**  This function sets the view to be drawn to the window,
  *  and draws everything related to state. 
  */
void GameStateEditor::draw(const float delta_time) {
  this->game->game_window.setView(this->_editorView);
  this->game->game_window.clear(sf::Color::Black);

  //Draw map
  this->game->map->draw(this->game->game_window);

  //Draw interface
  drawInterface(game->game_window);

  //Draw text
  if(game->saveClicked){
	  this->game->game_window.draw(testText);
	  this->game->game_window.draw(shownText);
	  //for(int i = 0 ; i < int(game->textList.size()) ; ++i){
	//		game->game_window.draw(game->textList[i]);
	 // }
  }
}

void GameStateEditor::update(const float delta_time) {
	if(currentButton != nullptr)
		currentButton->execute(game);
}

void GameStateEditor::handleInput() {
  sf::Event event;
  while(this->game->game_window.pollEvent(event)) {
    switch(event.type) {
      /** Close the window */
      case sf::Event::Closed: {
        game->game_window.close();
        break;
      }
	  case sf::Event::MouseButtonPressed: {
      localPosition = sf::Mouse::getPosition(this->game->game_window);
	  if(!game->pause){
	  for(int i = 0 ; i < int(buttonList.size()) ; ++i){
			  if(buttonList[i]->isClicked(float(localPosition.x), float(localPosition.y))){
				  currentButton = buttonList[i].get();
				  break;
			  }
		  }
		}
      }
	  case sf::Event::TextEntered:{
		 if(event.text.unicode == '\b' && !game->inputString.size() == 0){
			 game->inputString.pop_back();
			 this->testText.setString(game->inputString);
		 }
          else if (event.text.unicode < 128) {
                    game->inputString.push_back((char)event.text.unicode);
                    this->testText.setString(game->inputString);
				}
		  break;
	  }
	  case sf::Event::MouseMoved: {
		  localPosition = sf::Mouse::getPosition(this->game->game_window);
		  tileX = localPosition.x/32;
		  tileY = localPosition.y/32;
		  if(game->saveClicked)
			mapCommandLibrary(tileX, tileY);
		  break;
      }
      default: break;
    }
  }
}

void GameStateEditor::mapCommandLibrary(const int tileX, const int tileY){
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && game->tileSelect == Tile::START){
				game->map->addTile("resources/images/start.png", "start", tileX, tileY);	
			}
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && game->tileSelect == Tile::END){
				game->map->addTile("resources/images/end.png", "end", tileX, tileY);
			}
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && game->tileSelect == Tile::PATH){
				game->map->addTile("resources/images/path.png", "path", tileX, tileY);
			}
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && game->tileSelect == Tile::SCENERY){
				game->map->addTile("resources/images/scenery.png", "scenery", tileX, tileY);
			}
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && game->tileSelect == Tile::DEAD){
				game->map->addTile("resources/images/dead.png", "dead", tileX, tileY);
			}
			if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
				game->map->removeTile(tileX, tileY);
			}
			if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
				game->map->removeGameObject(tileX, tileY);
			}
			/*if(thisButton == sf::Mouse::Right){
				game->map->fillMap();
			}
			if(thisButton == sf::Mouse::Right){
				game->map->blankMap();
			}
			if(thisButton == sf::Mouse::Right){
				game->map->placeCritter("resources/images/critter.png", tileX, tileY);
			}
			if(thisButton == sf::Mouse::Right){
				game->map->placeTower("resources/images/tower.png", tileX, tileY);
			}
			if(thisButton == sf::Mouse::Right){
				game->map->load("testmap.xml");
			}
			if(thisButton == sf::Mouse::Right){
				game->map->save("testmap.xml");
			}
			if(thisButton == sf::Mouse::Right){
				if(game->map->isMapValid())
					cout << "map is valid: true" << endl;
				else
					cout << "map is valid: false" <<endl;
			}
		*/
}


void GameStateEditor::initializeInterface(){
	int y = game->map->getMapHeight();
	buttonList.emplace_back(new CloseEditorButton("resources/images/close.png", 10, y+1));
	buttonList.emplace_back(new SaveMapButton("resources/images/save.png", 9, y+1));
	buttonList.emplace_back(new TileSelectButton("resources/images/start.png",3,y+1,Tile::START));
	buttonList.emplace_back(new TileSelectButton("resources/images/end.png",4,y+1,Tile::END));
	buttonList.emplace_back(new TileSelectButton("resources/images/path.png",5,y+1,Tile::PATH));
	buttonList.emplace_back(new TileSelectButton("resources/images/scenery.png",6,y+1,Tile::SCENERY));
	buttonList.emplace_back(new TileSelectButton("resources/images/dead.png",7,y+1,Tile::DEAD));
}

void GameStateEditor::drawInterface(sf::RenderWindow& gameWindow){
	for (int i = 0 ; i < int(buttonList.size()) ; ++i){
			if(buttonList[i] != nullptr)
				buttonList[i]->draw(gameWindow);
		}
}