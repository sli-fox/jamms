#pragma once
#include <GameObject.h>

class Pathogen: public GameObject {
  public:
    enum PathogenType { CommonCold };

    Pathogen(PathogenType type, std::string name);
    ~Pathogen() {};

    std::string getName() const;
    Pathogen::PathogenType getType() const;

  private:
    std::string name;
    PathogenType type;
};