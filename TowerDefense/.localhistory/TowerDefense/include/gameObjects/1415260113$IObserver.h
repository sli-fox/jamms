#pragma once
#include <string>

class IObserver {

  public:
    void update() {
		std::cout << "I GOT UPDATED!" << std::endl;
	}

};