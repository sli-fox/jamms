#pragma once
#include <GameObject.h>

class Pathogen: public GameObject {
  public:
    Pathogen(std::string name);
    ~Pathogen() {};

  private:
    std::string name;
};