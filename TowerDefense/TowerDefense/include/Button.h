#pragma once
#include "command.h"

class Button :public Command{
public:
	Button(std::string textureName, int posX, int posY);

	virtual ~Button();
	virtual void execute(Game* game) = 0;
	bool isClicked (float mouseX, float mouseY);

};

