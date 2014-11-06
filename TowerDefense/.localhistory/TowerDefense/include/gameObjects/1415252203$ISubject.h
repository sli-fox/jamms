#pragma once
#include <string>
#include <gameObjects/IObserver.h>

class ISubject {
	vector < class IObserver * > observers;
  public:
	void attach(IObserver* obs)  {
        observers.push_back(obs);
    }
	void detach(IObserver* obs);
	void notify();

};