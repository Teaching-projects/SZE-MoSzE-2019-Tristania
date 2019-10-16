#include "Dir.hpp"

Dir::Dir(std::string name, Dir* parent) :name(name), parent(parent) {};

std::string Dir::getDirName() const {
	return name;
}

Dir* Dir::getParent() const {
	return parent;
}
