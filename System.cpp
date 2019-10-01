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

std::string System::getChild(std::string dirname) {
	for (auto &d : directories) {
		if (d->getParent() == dirname) {
			return d->getDirName();
		}
	}
	return "Error. Child not found!";
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

bool System::hasChildren(std::string dirname) {
	for (auto &d : directories) {
		if (d->getParent() == dirname) {
			return true;
		}
	}
	return false;
}

void System::rm(std::string dirname) {
	if (hasChildren(dirname)) {
		std::cerr << "This directory cannot be removed as it contains other directory/directories!\n";
	}
	else {
		for (unsigned i = 0; i < directories.size();i++) {
			if (directories[i]->getDirName() == dirname) {
				directories.erase(directories.begin() + i);
			}
		}
	}
}

void System::rmrf(std::string dirname) {
	for (auto const&d : directories) {
		while (hasChildren(dirname)) {
			rmrf(getChild(dirname));
		}
		rm(dirname);
	}
}

void System::printCore() {
	std::cout << "gabor-mbp:" << currentFolder << " gabor$ ";
}
