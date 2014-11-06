#pragma once
#include <string>

class ISubject {

  public:
    void attach(Tower* tower);
	void detach(Tower* tower);
	void notify();

};