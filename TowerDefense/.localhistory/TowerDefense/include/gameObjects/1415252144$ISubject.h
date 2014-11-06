#pragma once
#include <string>
#include <gameObjects/IObserver.h>

class ISubject {
	vector < class Observer * > observers;
  public:
	void attach(IObserver* tower);
	void detach(IObserver* tower);
	void notify();

};