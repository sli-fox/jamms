#include <gameStates/GameStateMapEditor.h>

/**  The constructor sets the view to the size of the window
*  and centers the view on the center of the window.
*/
GameStateMapEditor::GameStateMapEditor(Game* game) {
  this->game = game;

  	trackMapEvents = new TrackMapInput_c(Game::map);

	sf::Vector2f position = sf::Vector2f(this->game->game_window.getSize());
	this->_gameView.setSize(position);
	this->_guiView.setSize(position);

	sf::Vector2f center_position = 0.5f * position;
	this->_gameView.setCenter(center_position);
	this->_guiView.setCenter(center_position);
	
	initializeButtonMap();
	tileSelector = Tile::EMPTY;
	returnToMenu = false;
	pauseSave = false;
	pauseLoad = false;
	font.loadFromFile("resources/helveticaneue-webfont.ttf");

	mapBackdrop.load("resources/images/MapBackdrop.png");
	mapBackdrop.setPosition(0*32,0*32);
	mapX = Map::MAX_MAP_WIDTH;
	mapY = Map::MAX_MAP_HEIGHT;
	displayXsize.setString(std::to_string(mapX));
	displayYsize.setString(std::to_string(mapY));
	mapFiles = getFilesInDir("resources/maps/");
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

	if(buttonMap["RedoBtn"].spriteContains(localPosition)) {
	  userInputDisplay.setString(getRedoButtonSpecs());
	  this->game->game_window.draw(userInputDisplay);
	}
	else if(buttonMap["UndoBtn"].spriteContains(localPosition)) {
	  userInputDisplay.setString(getUndoButtonSpecs());
	  this->game->game_window.draw(userInputDisplay);
    }
	else if(buttonMap["saveBtn"].spriteContains(localPosition)) {
	  userInputDisplay.setString(getSaveButtonSpecs());
	  this->game->game_window.draw(userInputDisplay);
    }
	else if(buttonMap["playBtn"].spriteContains(localPosition)) {
	  userInputDisplay.setString(getPlayButtonSpecs());
	  this->game->game_window.draw(userInputDisplay);
    }
	else if(buttonMap["startTileBtn"].spriteContains(localPosition)) {
	  userInputDisplay.setString(getStartTileButtonSpecs());
	  this->game->game_window.draw(userInputDisplay);
    }
	else if(buttonMap["endTileBtn"].spriteContains(localPosition)) {
	  userInputDisplay.setString(getEndTileButtonSpecs());
	  this->game->game_window.draw(userInputDisplay);
    }
	else if(buttonMap["sceneryTileBtn"].spriteContains(localPosition)) {
	  userInputDisplay.setString(getSceneryTileButtonSpecs());
	  this->game->game_window.draw(userInputDisplay);
    }
	else if(buttonMap["deadTileBtn"].spriteContains(localPosition)) {
	  userInputDisplay.setString(getDeadTileButtonSpecs());
	  this->game->game_window.draw(userInputDisplay);
    }
	else if(buttonMap["pathTileBtn"].spriteContains(localPosition)) {
	  userInputDisplay.setString(getPathTileButtonSpecs());
	  this->game->game_window.draw(userInputDisplay);
    }
	else if(buttonMap["loadBtn"].spriteContains(localPosition)) {
	  userInputDisplay.setString(getLoadMapButtonSpecs());
	  this->game->game_window.draw(userInputDisplay);
    }
	//Draw buttons
	for(std::map<std::string, GameObject>::iterator it = buttonMap.begin() ; it != buttonMap.end() ; ++it)
		it->second.draw(this->game->game_window);

	//Draw text
	this->game->game_window.draw(displayXsize);
	this->game->game_window.draw(displayYsize);
	this->game->game_window.draw(systemOutput);
	this->game->game_window.draw(userInputDisplay);

	
	
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
		case sf::Event::KeyPressed:{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
				pauseSave = false;
				pauseLoad = false;
				systemOutput.setString("");
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
				if(pauseLoad){
					this->game->map.load(userInput);
					systemOutput.setString("");
					pauseLoad = false;
				}
				else if(pauseSave){
					this->game->map.save(userInput);
					systemOutput.setString("");
					pauseSave = false;
				}
			}else if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
				trackMapEvents->undo();
			}else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
				trackMapEvents->redo();
			}
			break;
									}
		case sf::Event::TextEntered:{
			if(event.text.unicode == '\b'){
				if(!userInput.empty())
					userInput.pop_back();
				userInputDisplay.setString(userInput);
			}
			else if (event.text.unicode < 128 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Return) ) {
				userInput.push_back((char)event.text.unicode);
				userInputDisplay.setString(userInput);
			}
			break;
									}
		default: break;
		}
	}
}

const vector<string> GameStateMapEditor::getFilesInDir(const string dir) {
	DIR *open_dir = NULL;
	struct dirent *dirp;
	vector<string> files;

	if ((open_dir = opendir(dir.c_str())) == NULL) {
		files.push_back("There are no maps");
	} else {
		while ((dirp = readdir(open_dir)) != NULL) {
			string filename = dirp->d_name;
			size_t find_pos = filename.find_last_of('.');
			if (filename.substr(find_pos) == ".xml" && filename != ".xml") {
				files.push_back(filename);
			}
		}
	}
	closedir(open_dir);

	return files;
}

void GameStateMapEditor::mapEditorCommandLibrary(){
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		if(this->game->map.getTile(tileX, tileY) != nullptr && this->game->map.getTile(tileX, tileY)->spriteContains(localPosition))
		{
			if( this->game->map.addTile(tileX, tileY, tileSelector) )
			trackMapEvents->recordAddTile(tileX, tileY, tileSelector);
		}
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
		{
			this->game->map.fillMap();
			trackMapEvents->recordFillMap( );
		}
		else if(buttonMap["resetMapBtn"].spriteContains(localPosition))
		{
			this->game->map.blankMap();
			trackMapEvents->recordResetMap();
		}
		else if(buttonMap["UndoBtn"].spriteContains(localPosition))
		{
			trackMapEvents->undo();
		}
		else if(buttonMap["RedoBtn"].spriteContains(localPosition))
		{
			trackMapEvents->redo();
		}

		else if(buttonMap["saveBtn"].spriteContains(localPosition)){
			if(!pauseSave){
				pauseSave = true;
				pauseLoad = false;
				systemOutput.setString("Please type in a name for the map (without the .xml extension) and then click save again:\n");
			}
			else if(pauseSave){
				pauseSave = false;
				this->game->map.save(userInput);
				systemOutput.setString("");
				mapFiles = getFilesInDir("resources/maps/");
			}
		}
		else if(buttonMap["loadBtn"].spriteContains(localPosition)){
			if(!pauseLoad){
				pauseLoad = true;
				pauseSave = false;
				string tempString = "Here are the available map files, please type in the full extension of the map and click load again:\n";
				for(int i = 0 ; i < int(mapFiles.size()) ; ++i){
					tempString.append(mapFiles[i] + "\n");
				}
				systemOutput.setString(tempString);
			}
			else if (pauseLoad){
				pauseLoad = false;
				this->game->map.load(userInput);
				systemOutput.setString("");
			}
		}
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
		else if(buttonMap["validateMapBtn"].spriteContains(localPosition)){
			if(this->game->map.isMapValid())
				cout << "map is valid" << endl;
			else
				cout << "map not valid" << endl;
		}
		else if(buttonMap["setMapSizeBtn"].spriteContains(localPosition)){
			this->game->map.resetMap();
			this->game->map.setMapSize(mapX, mapY);
			this->game->map.blankMap();
		}
		else if(buttonMap["plusSizeBtnX"].spriteContains(localPosition)){
			if(mapX < Map::MAX_MAP_WIDTH){
				++mapX;
				displayXsize.setString(std::to_string(mapX));
			}
		}
		else if(buttonMap["minusSizeBtnX"].spriteContains(localPosition)){
			if(mapX > 0){
				--mapX;
				displayXsize.setString(std::to_string(mapX));
			}
		}
		else if(buttonMap["plusSizeBtnY"].spriteContains(localPosition)){
			if(mapY < Map::MAX_MAP_HEIGHT){
				++mapY;
				displayYsize.setString(std::to_string(mapY));
			}
		}
		else if(buttonMap["minusSizeBtnY"].spriteContains(localPosition)){
			if(mapY > 0){
				--mapY;
				displayYsize.setString(std::to_string(mapY));
			}
		}
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

	GameObject setMapSizeBtn;
	setMapSizeBtn.load(imagePath + "SetMapSize.png");
	setMapSizeBtn.setPosition(3*32,22*32);
	buttonMap.emplace("setMapSizeBtn", setMapSizeBtn);

	GameObject minusSizeBtnX;
	minusSizeBtnX.load(imagePath + "MinusSizeBtn.png");
	minusSizeBtnX.setPosition(3*32,20*32);
	buttonMap.emplace("minusSizeBtnX", minusSizeBtnX);

	GameObject plusSizeBtnX;
	plusSizeBtnX.load(imagePath + "PlusSizeBtn.png");
	plusSizeBtnX.setPosition(4.5*32,20*32);
	buttonMap.emplace("plusSizeBtnX", plusSizeBtnX);

	GameObject undoMapBtn;
	undoMapBtn.load(imagePath + "UndoBtn.png");
	undoMapBtn.setPosition(0*32,22*32);
	buttonMap.emplace("UndoBtn", undoMapBtn); 

	GameObject redoMapBtn;
	redoMapBtn.load(imagePath + "RedoBtn.png");
	redoMapBtn.setPosition(0*32,23*32);
	buttonMap.emplace("RedoBtn", redoMapBtn);

	GameObject displayX;
	displayX.load(imagePath + "blank.png");
	displayX.setPosition(3.5*32,20*32);
	buttonMap.emplace("displayX", displayX);
	displayXsize.setFont(font);
	displayXsize.setPosition(3.5*32+6,20*32+6);
	displayXsize.setColor(sf::Color::Black);
	displayXsize.setCharacterSize(16);

	GameObject displayY;
	displayY.load(imagePath + "blank.png");
	displayY.setPosition(3.5*32,21*32);
	buttonMap.emplace("displayY", displayY);
	displayYsize.setFont(font);
	displayYsize.setPosition(3.5*32+6,21*32+6);
	displayYsize.setColor(sf::Color::Black);
	displayYsize.setCharacterSize(16);

	GameObject widthDisplay;
	widthDisplay.load(imagePath + "width.png");
	widthDisplay.setPosition(5*32,20*32);
	buttonMap.emplace("widthDisplay", widthDisplay);

	GameObject heightDisplay;
	heightDisplay.load(imagePath + "height.png");
	heightDisplay.setPosition(5*32,21*32);
	buttonMap.emplace("heightDisplay", heightDisplay);

	GameObject minusSizeBtnY;
	minusSizeBtnY.load(imagePath + "MinusSizeBtn.png");
	minusSizeBtnY.setPosition(3*32,21*32);
	buttonMap.emplace("minusSizeBtnY", minusSizeBtnY);

	GameObject plusSizeBtnY;
	plusSizeBtnY.load(imagePath + "PlusSizeBtn.png");
	plusSizeBtnY.setPosition(4.5*32,21*32);
	buttonMap.emplace("plusSizeBtnY", plusSizeBtnY);

	GameObject textBoxOutput;
	textBoxOutput.load(imagePath + "TextBox.png");
	textBoxOutput.setPosition(6*32,12*32);
	buttonMap.emplace("textBoxOutput", textBoxOutput);
	systemOutput.setFont(font);
	systemOutput.setPosition(6*32+4,12*32);
	systemOutput.setColor(sf::Color::Black);
	systemOutput.setCharacterSize(14);

	GameObject textBoxInput;
	textBoxInput.load(imagePath + "TextBox.png");
	textBoxInput.setPosition(6*32,18*32);
	buttonMap.emplace("textBoxInput", textBoxInput);
	userInputDisplay.setFont(font);
	userInputDisplay.setPosition(6*32+4,18*32);
	userInputDisplay.setColor(sf::Color::Black);
	userInputDisplay.setCharacterSize(14);
}

std::string GameStateMapEditor::getRedoButtonSpecs() {
	std::stringstream output;
	output << "Press to redo  map tiles" << std::endl;
	
	return output.str();
}
std::string GameStateMapEditor::getUndoButtonSpecs() {
	std::stringstream output;
	output << "Press to Undo  map tiles" << std::endl;
	
	return output.str();
}
std::string GameStateMapEditor::getSaveButtonSpecs() {
	std::stringstream output;
	output << "Press to save the map created" << std::endl;
	
	return output.str();
}

std::string GameStateMapEditor::getPlayButtonSpecs() {
	std::stringstream output;
	output << "Press to start the game" << std::endl;
	
	return output.str();
}
std::string GameStateMapEditor::getStartTileButtonSpecs() {
	std::stringstream output;
	output << "Start tile of the map" << std::endl;
	
	return output.str();
}
std::string GameStateMapEditor::getEndTileButtonSpecs() {
	std::stringstream output;
	output << "End tile of the map" << std::endl;
	
	return output.str();
}
std::string GameStateMapEditor::getPathTileButtonSpecs() {
	std::stringstream output;
	output << "Path tile of the map" << std::endl;
	
	return output.str();
}
std::string GameStateMapEditor::getSceneryTileButtonSpecs() {
	std::stringstream output;
	output << "Scenery tile of the map" << std::endl;
	
	return output.str();
}
std::string GameStateMapEditor::getDeadTileButtonSpecs() {
	std::stringstream output;
	output << "Dead tile of the map" << std::endl;
	output << "No tower could be placed on it" << std::endl;
	return output.str();
}
std::string GameStateMapEditor::getLoadMapButtonSpecs() {
	std::stringstream output;
	output << "Press to see all the saved maps" << std::endl;
	output << "Type the name of map you would like to load" << std::endl;
	return output.str();
}