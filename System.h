#ifndef _system_h_
#define _system_h_


//#include "Dir.h"
#include <list>
#include <iostream>
#include <map>

class System{
	//std::list<Dir*> directories;
	std::string currentFolder;
	std::map <std::string, std::string> directories;
	std::map <std::string, std::string>::iterator it;
	std::string path;
	public:
		System();
		void mkdir(std::string);
		bool alreadyExists(std::string);
		void rm(std::string);
		void ls();
		void cd(std::string);
		void cdBack();
		void printCore();
};

#endif
