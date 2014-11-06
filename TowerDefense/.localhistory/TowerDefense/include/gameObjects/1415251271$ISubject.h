#pragma once
#include <string>
#include <gameObjects/Tower.h>

class ISubject {

  public:
    void attach(Tower* tower);
	void detach();
	void notify();

};