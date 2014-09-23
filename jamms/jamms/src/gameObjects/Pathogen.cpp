#include <Pathogen.h>

Pathogen::Pathogen(PathogenType type, std::string name) : type(type), name(name) {}

std::string Pathogen::getName() const {
  return name;
}

Pathogen::PathogenType Pathogen::getType() const {
  return type;
}
