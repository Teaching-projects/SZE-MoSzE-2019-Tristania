#include "System.h"

System::System() {
	currentFolder = "/";
	path = "/";
};

void System::mkdir(std::string dirname) {
	//directories.push_back(new Dir(dirname, current));
	directories.insert(std::pair<std::string, std::string>(dirname,currentFolder));
}

void System::rm(std::string dirname) {
	for (it = directories.begin(); it != directories.end(); it++) {
		if (it->second == currentFolder && it->first == dirname)
		{
			directories.erase(dirname);
		}
		
	}
}

void System::ls() {
	for (it = directories.begin(); it != directories.end(); it++) {
		if (it->second == currentFolder) {
			std::cout << it->first << "\n";
		}
	}
}

bool System::alreadyExists(std::string dirname) {
	for (it = directories.begin(); it != directories.end(); it++) {
		if (it->first == dirname && it->second == currentFolder)
		{
			return true;
		}
	}
	return false;
}

void System::cd(std::string dirname) {
	currentFolder = dirname;
	path += dirname + "/";
}

void System::cdBack() {
	if (currentFolder != "/") {
		for (it = directories.begin(); it != directories.end(); it++) {
			if (it->first == currentFolder)
			{
				path.erase(path.end() - (currentFolder.length() + 1), path.end());
				currentFolder = it->second;
			}
		}
	}
	else { std::cerr << "You are in root!" << std::endl; }


}
void System::printCore() {
	std::cout << "username:" << path << " & ";
}
