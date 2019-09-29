#ifndef _dir_h_
#define _dir_h_

#include <string>
#include <iostream>

class Dir {
	std::string name;
	std::string parent;
public:
	Dir(std::string, std::string);
	std::string getDirName();
	std::string getParent();
};

#endif#pragma once
