#include <gameStates/GameStateMapEditor.h>

/**  The constructor sets the view to the size of the window
*  and centers the view on the center of the window.
*/
GameStateMapEditor::GameStateMapEditor(Game* game) {
	this->game = game;

	sf::Vector2f position = sf::Vector2f(this->game->game_window.getSize());
	this->_gameView.setSize(position);
	this->_guiView.setSize(position);

	sf::Vector2f center_position = 0.5f * position;
	this->_gameView.setCenter(center_position);
	this->_guiView.setCenter(center_position);
	
	initializeButtonMap();
	tileSelector = Tile::EMPTY;
	returnToMenu = false;

	mapBackdrop.load("resources/images/MapBackdrop.png");
	mapBackdrop.setPosition(0*32,0*32);
}

/**  This function sets the view to be drawn to the window,
*  and draws everything related to state. 
*/
void GameStateMapEditor::draw(const float delta_time) {
	this->game->game_window.setView(this->_gameView);
	this->game->game_window.clear(sf::Color::Black);

	//Draw map
	mapBackdrop.draw(this->game->game_window);
	this->game->map.draw(this->game->game_window);

	//Draw buttons
	for(std::map<std::string, GameObject>::iterator it = buttonMap.begin() ; it != buttonMap.end() ; ++it)
		it->second.draw(this->game->game_window);
}

void GameStateMapEditor::update(const float delta_time) {

}

void GameStateMapEditor::handleInput() {
	sf::Event event;
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
			mapEditorCommandLibrary();
			buttonCommandLibrary();
			break;
											}
		case sf::Event::MouseMoved: {
			mapEditorCommandLibrary();
			break;
									}
		default: break;
		}
	}
}

void GameStateMapEditor::mapEditorCommandLibrary(){
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		if(this->game->map.getTile(tileX, tileY) != nullptr && this->game->map.getTile(tileX, tileY)->spriteContains(localPosition))
			this->game->map.addTile(tileX, tileY, tileSelector);
	}
	else if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
		if(this->game->map.getTile(tileX, tileY) != nullptr && this->game->map.getTile(tileX, tileY)->spriteContains(localPosition)){
			this->game->map.removeTile(tileX, tileY);
			this->game->map.removeGameObject(tileX, tileY);
		}
	}		
}

void GameStateMapEditor::buttonCommandLibrary(){
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		if(buttonMap["startTileBtn"].spriteContains(localPosition))
			tileSelector = Tile::START;
		else if(buttonMap["endTileBtn"].spriteContains(localPosition))
			tileSelector = Tile::END;
		else if(buttonMap["pathTileBtn"].spriteContains(localPosition))
			tileSelector = Tile::PATH;
		else if(buttonMap["sceneryTileBtn"].spriteContains(localPosition))
			tileSelector = Tile::SCENERY;
		else if(buttonMap["deadTileBtn"].spriteContains(localPosition))
			tileSelector = Tile::DEAD;
		else if(buttonMap["fillMapBtn"].spriteContains(localPosition))
			this->game->map.fillMap();
		else if(buttonMap["resetMapBtn"].spriteContains(localPosition))
			this->game->map.blankMap();
		else if(buttonMap["saveBtn"].spriteContains(localPosition))
			this->game->map.save("testmap2.xml");
		else if(buttonMap["loadBtn"].spriteContains(localPosition))
			this->game->map.load("testmap2.xml");
		else if(buttonMap["playBtn"].spriteContains(localPosition)){
			if(game->map.isMapValid())
				this->game->pushState(new GameStatePlay(this->game));
			else
				cout << "map is not valid, cannot play" << endl;
		}
		else if(buttonMap["menuBtn"].spriteContains(localPosition)){
			returnToMenu = true;
			this->game->popState();
		}
		else if(buttonMap["validateMapBtn"].spriteContains(localPosition))
			cout << this->game->map.isMapValid() << endl;
	}
}

void GameStateMapEditor::initializeButtonMap(){
	string imagePath = "resources/images/";

	GameObject tilePalette;
	tilePalette.load(imagePath + "TilePalette.png");
	tilePalette.setPosition(0*32,12*32);
	buttonMap.emplace("tilePalette", tilePalette);
	
	GameObject startTileBtn;
	startTileBtn.load(imagePath + "start.png");
	startTileBtn.setPosition(0*32,13*32);
	buttonMap.emplace("startTileBtn", startTileBtn);

	GameObject endTileBtn;
	endTileBtn.load(imagePath + "end.png");
	endTileBtn.setPosition(1*32,13*32);
	buttonMap.emplace("endTileBtn", endTileBtn);

	GameObject pathTileBtn;
	pathTileBtn.load(imagePath + "path.png");
	pathTileBtn.setPosition(2*32,13*32);
	buttonMap.emplace("pathTileBtn", pathTileBtn);

	GameObject sceneryTileBtn;
	sceneryTileBtn.load(imagePath + "scenery.png");
	sceneryTileBtn.setPosition(3*32,13*32);
	buttonMap.emplace("sceneryTileBtn", sceneryTileBtn);

	GameObject deadTileBtn;
	deadTileBtn.load(imagePath + "dead.png");
	deadTileBtn.setPosition(4*32,13*32);
	buttonMap.emplace("deadTileBtn", deadTileBtn);

	GameObject emptyTileBtn;
	emptyTileBtn.load(imagePath + "blank.png");
	emptyTileBtn.setPosition(5*32,13*32);
	buttonMap.emplace("emptyTileBtn", emptyTileBtn);

	GameObject fillMapBtn;
	fillMapBtn.load(imagePath + "FillMapBtn.png");
	fillMapBtn.setPosition(0*32,14*32);
	buttonMap.emplace("fillMapBtn", fillMapBtn);

	GameObject resetMapBtn;
	resetMapBtn.load(imagePath + "ResetMapBtn.png");
	resetMapBtn.setPosition(3*32,14*32);
	buttonMap.emplace("resetMapBtn", resetMapBtn);

	GameObject saveBtn;
	saveBtn.load(imagePath + "SaveBtn.png");
	saveBtn.setPosition(0*32,16*32);
	buttonMap.emplace("saveBtn", saveBtn);

	GameObject loadBtn;
	loadBtn.load(imagePath + "LoadBtn.png");
	loadBtn.setPosition(3*32,16*32);
	buttonMap.emplace("loadBtn", loadBtn);

	GameObject playBtn;
	playBtn.load(imagePath + "PlayBtn.png");
	playBtn.setPosition(0*32,18*32);
	buttonMap.emplace("playBtn", playBtn);

	GameObject menuBtn;
	menuBtn.load(imagePath + "MenuBtn.png");
	menuBtn.setPosition(3*32,18*32);
	buttonMap.emplace("menuBtn", menuBtn);

	GameObject validateMapBtn;
	validateMapBtn.load(imagePath + "ValidateMapBtn.png");
	validateMapBtn.setPosition(0*32,20*32);
	buttonMap.emplace("validateMapBtn", validateMapBtn);

	GameObject textBoxOutput;
	textBoxOutput.load(imagePath + "TextBox.png");
	textBoxOutput.setPosition(6*32,12*32);
	buttonMap.emplace("textBoxOutput", textBoxOutput);

	GameObject textBoxInput;
	textBoxInput.load(imagePath + "TextBox.png");
	textBoxInput.setPosition(6*32,18*32);
	buttonMap.emplace("textBoxInput", textBoxInput);
}