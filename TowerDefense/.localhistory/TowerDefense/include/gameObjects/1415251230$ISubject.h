#pragma once
#include <string>

class ISubject {

  public:
    void attach();
	void detach();
	void notify();

};