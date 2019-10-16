#pragma	once

#include <string>
#include <iostream>

class Dir {
    std::string name;
	Dir* parent;
public:
	Dir(std::string, Dir*);
	std::string getDirName() const;
	Dir* getParent() const;
};
