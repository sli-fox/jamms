#pragma once
#include <gameObjects\GameObject.h>
#include <Game.h>

class Command : public GameObject{
public:
	Command(){}

	virtual ~Command(){}

	virtual void execute(Game* game) = 0;
};

