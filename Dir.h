#pragma	once

#include <string>
#include <iostream>

class Dir {
	std::string name;
	std::string parent;
public:
	Dir(std::string, std::string);
	std::string getDirName() const;
	std::string getParent() const;
};