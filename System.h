#ifndef _system_h_
#define _system_h_


#include "Dir.h"
#include <list>
#include <iostream>

class System{
	std::list<Dir*> directories;
	std::string currentFolder;
	std::string path;
	public:
		System();
		void mkdir(std::string, std::string);
		void ls();
		void cd(std::string);
		void cdBack();
		void printCore();
		std::string getCurrent();
};

#endif
