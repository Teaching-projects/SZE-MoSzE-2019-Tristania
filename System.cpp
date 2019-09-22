#include "System.h"

System::System() {
	currentFolder = "/";
	path = "/";
};

void System::mkdir(std::string dirname, std::string current) {
	directories.push_back(new Dir(dirname, current));
}

std::string System::getCurrent() {
	return currentFolder;
}

void System::ls() {
	for (auto &v : directories) {
		if (v->getParent() == System::getCurrent()) {
			std::cout << v->getDirName() << "\n";
		}
	}
}

bool System::alreadyExists(std::string dirname) {
	bool toReturn = false;
	for (auto &d : directories) {
		if (d->getDirName() == dirname) {
			toReturn = true;
		}
	}
	return toReturn;
}

void System::cd(std::string dirname) {
	currentFolder = dirname;
	path += dirname + "/";
}

void System::cdBack() {
	if (currentFolder != "/") {
		for (auto &v : directories) {
			if (v->getDirName() == currentFolder) {
				path.erase(path.end() - (getCurrent().length() + 1), path.end());
				currentFolder = v->getParent();
			}
		}
	}
	else { std::cerr << "You are in root!" << std::endl; }


}
void System::printCore() {
	std::cout << "username:" << path << " & ";
}
