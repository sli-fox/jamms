#include "Button.h"


Button::Button(std::string textureName, int posX, int posY){
	load(textureName);
	setPosition(float(posX*32), float(posY*32));
	file_name = textureName;

}

Button::~Button(){

}

bool Button::isClicked (float mouseX, float mouseY){
	return getSpriteBounds().contains(mouseX, mouseY);
}
