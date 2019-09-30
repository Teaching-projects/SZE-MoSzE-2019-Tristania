#ifndef _system_h_
#define _system_h_

#include "Dir.h"
#include <vector>
#include <iostream>

class System {
	std::vector<Dir*> directories;
	std::string currentFolder;
	std::string path;
public:
	System();
	bool hasChildren(std::string);
	bool alreadyExists(std::string);

	void mkdir(std::string, std::string);
	void ls();
	void cd(std::string);
	void cdBack();
	void rm(std::string);
	void rmrf(std::string);
	void printCore();

	std::string getCurrent();
	std::string getChild(std::string);
};

#endif
#pragma once
