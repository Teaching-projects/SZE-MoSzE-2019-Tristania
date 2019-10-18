#pragma once

#include "Dir.hpp"
#include "File.hpp"
#include <vector>
#include <iostream>

class NoDirectoryExc : public std::exception {
    std::string what = "No directory found with the given name. Please try again with another name!\n";
public:
    std::string getWhat() { return what; };
};

class System {
	std::vector<Dir*> directories;
    std::vector<File*> files;
	Dir* currentFolder;
public:
	System();
    ~System();
	std::string getCurrent() const;
	std::string getChild(std::string) const;

	void printCore() const;

	bool alreadyExists(std::string) const;
	bool hasChildren(std::string) const;
    
    void goToRoot();
    std::string goToFolder(std::string);

	void mkdir(std::string);
    void touch(std::string);
	void ls(std::string);
	void cd(std::string);
	void cdBack();
	void rm(std::string);
	void rmrf(std::string);
};
