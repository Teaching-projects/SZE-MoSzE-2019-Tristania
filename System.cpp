#include "System.hpp"
#include <sstream>

System::System() {
    currentFolder = new Dir("root", nullptr);
};

std::string System::getChild(std::string dirname) const {
	for (auto &d : directories) {
		if (d->getParent()->getDirName() == dirname) {
			return d->getDirName();
		}
	}
	return "Error. Child not found!";
}

void System::printCore() const {
	std::cout << "gabor-mbp:" << currentFolder->getDirName() << " gabor$ ";
}

bool System::alreadyExists(std::string dirname) const {
	bool toReturn = false;
	for (auto &d : directories) {
		if (d->getDirName() == dirname && d->getParent()->getDirName() == currentFolder->getDirName()) {
			toReturn = true;
		}
	}
    for (auto &f : files) {
        if (f->getName() == dirname && f->getParent()->getDirName() == currentFolder->getDirName()) {
            toReturn = true;
        }
    }
    
	return toReturn;
}

bool System::hasChildren(std::string dirname) const {
	for (auto &d : directories) {
		if (d->getParent()->getDirName() == dirname) {
			return true;
		}
	}
	return false;
}

void System::goToRoot(){
    while (currentFolder->getDirName() != "root") {
        cdBack();
    }
}

std::string System::goToFolder(std::string dirname) {
    std::stringstream ss(dirname);
    std::string token;
    std::vector<std::string> tokens;
    while(getline(ss, token, '/')) {
        tokens.push_back(token);
    }
    std::string workdir = tokens.back();
    tokens.pop_back();
    for(auto &t : tokens) {
        cd(t);
    }
    return workdir;
}

void System::mkdir(std::string dirname) {
    if (dirname.find("/") != std::string::npos) {
        Dir* current = currentFolder;
        goToRoot();
        
        directories.push_back(new Dir(goToFolder(dirname),currentFolder));
        currentFolder = current;
        
    } else {
        if (!alreadyExists(dirname)) {
            directories.push_back(new Dir(dirname, currentFolder));
        } else std::cerr << "This directory name is already taken. Please try again with another name!" <<std::endl;
    }
}

void System::ls() {
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
    if (dirname.find("/") != std::string::npos) {
        goToRoot();
        std::stringstream ss(dirname);
        std::string token;
        while (getline(ss, token, '/')) {
            cd(token);
        }
    } else {
        if (alreadyExists(dirname)) {
            for(Dir* &d : directories) {
                if (d->getDirName() == dirname && d->getParent() == currentFolder) {
                    currentFolder = d;
                }
            }
        } else std::cerr << "No directory found with the given name. Please try again with another name!" << std::endl;
    }
}

void System::cdBack() {
	if (currentFolder->getDirName() != "root") {
		for (auto &v : directories) {
			if (v->getDirName() == currentFolder->getDirName()) {
				currentFolder = v->getParent();
			}
		}
	}
	else { std::cerr << "You are in root!" << std::endl; }

}

void System::rm(std::string dirname) {
    if (dirname.find("/") != std::string::npos) {
        Dir* current = currentFolder;
        goToRoot();
        std::string workdir = goToFolder(dirname);
        if (hasChildren(workdir)) {
            std::cerr << "This directory cannot be removed as it contains other directories/ files!\n";
        } else if (!alreadyExists(workdir)) {
            std::cerr << "No directory found with the given name. Please try again with another name!" << std::endl;
        }
        else {
            for (unsigned i = 0; i < directories.size();i++) {
                if (directories[i]->getDirName() == workdir) {
                    directories.erase(directories.begin() + i);
                }
            }
            
            for (unsigned i = 0; i< files.size();i++) {
                if (files[i]->getName() == dirname) {
                    files.erase(files.begin() + i);
                }
            }
        }
        currentFolder = current;
    }
    else {
        if (hasChildren(dirname)) {
            std::cerr << "This directory cannot be removed as it contains other directories/ files!\n";
        } else if (!alreadyExists(dirname)) {
            std::cerr << "No directory found with the given name. Please try again with another name!" << std::endl;
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
}

void System::rmrf(std::string dirname) {
    if (!alreadyExists(dirname)) {
        std::cerr << "No directory found with the given name. Please try again with another name!" << std::endl;
    } else {
        while (hasChildren(dirname)) {
            rmrf(getChild(dirname));
        }
        rm(dirname);
    }
}

void System::touch(std::string fname) {
    if (fname.find("/") != std::string::npos) {
        Dir* current = currentFolder;
        goToRoot();
        
        files.push_back(new File(goToFolder(fname),currentFolder));
        currentFolder = current;
        
    } else {
        if (!alreadyExists(fname)) {
            files.push_back(new File(fname, currentFolder));
        } else std::cerr << "This file name is already taken. Please try again with another name!" <<std::endl;
    }
}
