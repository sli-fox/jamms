#pragma once
#include <string>
#include <gameObjects/IObserver.h>

class ISubject {

  public:
	void attach(IObserver* tower);
	void detach(IObserver* tower);
	void notify();

};