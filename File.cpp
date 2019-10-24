#include "File.hpp"


File::File(std::string filename, Dir* parent) : name(filename), parent(parent) {}

std::string File::getName() { return name; }

Dir* File::getParent() { return parent; }

