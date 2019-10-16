#pragma once

#include "Dir.hpp"
#include "File.hpp"
#include <vector>
#include <iostream>

class System {
	std::vector<Dir*> directories;
    std::vector<File*> files;
	Dir* currentFolder;
public:
	System();
	std::string getCurrent() const;
	std::string getChild(std::string) const;

	void printCore() const;

	bool alreadyExists(std::string) const;
	bool hasChildren(std::string) const;
    
    void goToRoot();
    std::string goToFolder(std::string);

	void mkdir(std::string);
    void touch(std::string);
	void ls();
	void cd(std::string);
	void cdBack();
	void rm(std::string);
	void rmrf(std::string);
};
