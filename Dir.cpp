#include "Dir.hpp"

Dir::Dir(std::string name, std::string parent) :name(name), parent(parent) {};

std::string Dir::getDirName() const {
	return name;
}

std::string Dir::getParent() const {
	return parent;
}
