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

class NoDirClassExc : public std::exception {
    std::string what;
public:
    NoDirClassExc() { what = ""; };
    NoDirClassExc(std::string whatis) { what = whatis; }
    std::string getWhat() { return what; }
};


class System {
	Dir* currentFolder;
public:
	System();
    ~System();
	std::string getCurrent() const;
	Node* getChild(Dir*) const;
    Node* stringToNode(std::string);

	void printCore() const;

	bool alreadyExists(std::string) const;
	bool hasChildren(Dir*) const;
    
    void goToRoot();
    std::string goToFolder(std::string);

	void mkdir(std::string);
    void touch(std::string);
	void ls(std::string);
	void cd(std::string);
	void cdBack();
	void rm(std::string);
	void rmrf(std::string);
	void echo(std::string, std::string);
};
