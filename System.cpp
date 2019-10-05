#include "System.hpp"

System::System() {
	currentFolder = "/";
	path = "/";
};

std::string System::getChild(std::string dirname) const {
	for (auto &d : directories) {
		if (d->getParent() == dirname) {
			return d->getDirName();
		}
	}
	return "Error. Child not found!";
}

void System::printCore() const {
	std::cout << "gabor-mbp:" << currentFolder << " gabor$ ";
}

bool System::alreadyExists(std::string dirname) const {
	bool toReturn = false;
	for (auto &d : directories) {
		if (d->getDirName() == dirname && d->getParent() == currentFolder) {
			toReturn = true;
		}
	}
    for (auto &f : files) {
        if (f->getName() == dirname && f->getParent() == currentFolder) {
            toReturn = true;
        }
    }
    
	return toReturn;
}

bool System::hasChildren(std::string dirname) const {
	for (auto &d : directories) {
		if (d->getParent() == dirname) {
			return true;
		}
	}
	return false;
}

void System::mkdir(std::string dirname) {
	directories.push_back(new Dir(dirname, currentFolder));
}

void System::ls() const {
	for (auto &d : directories) {
		if (d->getParent() == currentFolder) {
            std::cout <<d->getDirName() <<"/" <<std::endl;;
		}
	}
    for (auto &f : files) {
        if (f->getParent() == currentFolder) {
            std::cout <<f->getName() <<std::endl;
        }
    }
}

void System::cd(std::string dirname) {
	currentFolder = dirname;
	path += dirname + "/";
}

void System::cdBack() {
	if (currentFolder != "/") {
		for (auto &v : directories) {
			if (v->getDirName() == currentFolder) {
				currentFolder = v->getParent();
			}
		}
	}
	else { std::cerr << "You are in root!" << std::endl; }

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

    for (unsigned i = 0; i< files.size();i++) {
        if (files[i]->getName() == dirname) {
            files.erase(files.begin() + i);
        }
    }
}

void System::rmrf(std::string dirname) {
    while (hasChildren(dirname)) {
        rmrf(getChild(dirname));
    }
    rm(dirname);
}

void System::touch(std::string fname) {
    if (!alreadyExists(fname)) {
        files.push_back(new File(fname, currentFolder));
    } else std::cerr <<"This name already taken, please choose other."<<std::endl;
}
