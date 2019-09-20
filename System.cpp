#include "System.h"

System::System(){
	currentFolder = "/";
	path = "/";
};



void System::mkdir(std::string dirname, std::string current){
	directories.push_back(new Dir(dirname, current));
}

std::string System::getCurrent(){
	return currentFolder;
}

void System::ls(){
	for (auto &v : directories) {
		if (v->getParent() == System::getCurrent())	{
			std::cout << v->getDirName() << "\n";
		}
	}
}

void System::cd(std::string dirname){
	currentFolder = dirname;
	path += dirname + "/";
}

void System::cdBack(){
	for (auto &v : directories) {
		if (v->getDirName() == currentFolder && currentFolder != "/"){
			path.erase(path.end()- (getCurrent().length() + 1), path.end());
			currentFolder = v->getParent();
		} else
		{
			std::cout << "You are in root folder..." << std::endl;
		}
		
	}
}
void System::printCore(){
	std::cout <<"username:" << path<< " & "; 
}
