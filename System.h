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
	void mkdir(std::string, std::string);
	bool alreadyExists(std::string);
	void ls();
	void cd(std::string);
	void cdBack();
	void rm(std::string);
	void printCore();
	std::string getCurrent();
};

#endif
#pragma once
