#pragma once
#include <string>
#include <gameObjects/ISubject.h>

class IObserver {

  public:
	  virtual void update(ISubject* subject) = 0;

};