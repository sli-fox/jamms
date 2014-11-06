#pragma once
#include <string>
#include <gameObjects/IObserver.h>

class ISubject {

  public:
	void attach(Tower tower);
	void detach();
	void notify();

};