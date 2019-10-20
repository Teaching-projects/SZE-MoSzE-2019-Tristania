#include "File.hpp"


File::File(std::string filename, Dir* parent, std::string content) : name(filename), parent(parent), content(content) {}

std::string File::getName() { return name; }

Dir* File::getParent() { return parent; }

