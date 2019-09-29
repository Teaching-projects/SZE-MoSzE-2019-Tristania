#include "Dir.h"

Dir::Dir(std::string name, std::string parent) :name(name), parent(parent) {};

std::string Dir::getDirName() {
	return name;
}

std::string Dir::getParent() {
	return parent;
}