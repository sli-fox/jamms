#pragma once
#include <string>
#include <gameObjects/IObserver.h>

class ISubject {

	vector < class IObserver * > observers;

  public:
	void attach(IObserver* obs)  {
        observers.push_back(obs);
    }
	void detach(IObserver* obs) {
        observers.pop_back();
	}
	void notify() {
		for (int i = 0; i < observers.size(); i++)
			observers[i]->update();
	}

};