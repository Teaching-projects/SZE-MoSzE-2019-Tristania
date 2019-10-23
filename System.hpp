#pragma once

#include "Dir.hpp"
#include "File.hpp"
#include <vector>
#include <iostream>

class System {
	std::vector<Dir*> directories;
    std::vector<File*> files;
	std::string currentFolder;
	std::string path;
public:
	System();
	std::string getCurrent() const;
	std::string getChild(std::string) const;

	void printCore() const;

	bool alreadyExists(std::string) const;
	bool hasChildren(std::string) const;

	void mkdir(std::string);
    void touch(std::string);
	void ls() const;
	void cd(std::string);
	void cdBack();
	void rm(std::string);
	void rmrf(std::string);
	void echo(std::string, std::string);
};
