#include "System.hpp"
#include <sstream>

System::System() {
    currentFolder = new Dir("root", nullptr);
    directories.push_back(currentFolder);
};

System::~System(){
    for (auto &d : directories) {
        delete d;
    }
    for (auto &f : files) {
        delete f;
    }
    directories.clear();
    files.clear();
}

std::string System::getChild(std::string dirname) const {
	for (auto &d : directories) {
		if (d->getParent()->getName() == dirname) {
			return d->getName();
		}
	}
    for (auto &f : files) {
        if (f->getParent()->getName() == dirname) {
            return f->getName();
        }
    }
	return "Error. Child not found!";
}

void System::printCore() const {
	std::cout << "gabor-mbp:" << currentFolder->getName() << " gabor$ ";
}

bool System::alreadyExists(std::string dirname) const {
	bool toReturn = false;
	for (auto &d : directories) {
		if (d->getName() == dirname && d->getParent()->getName() == currentFolder->getName()) {
			toReturn = true;
		}
	}
    for (auto &f : files) {
        if (f->getName() == dirname && f->getParent()->getName() == currentFolder->getName()) {
            toReturn = true;
        }
    }
    
	return toReturn;
}

bool System::hasChildren(std::string dirname) const {
	for (auto &d : directories) {
		if (d->getParent()->getName() == dirname) {
			return true;
		}
	}
    for ( auto &f : files) {
        if (f->getParent()->getName() == dirname) {
            return true;
        }
    }
    
	return false;
}

void System::goToRoot(){
    while (currentFolder->getParent() != nullptr) {
        cdBack();
    }
}

std::string System::goToFolder(std::string dirname) {
    
    //TODO:ize/bize/ rákérdezni az mit tud!!!!
    
    std::stringstream ss(dirname);
    std::string token;
    std::vector<std::string> tokens;
    while(getline(ss, token, '/')) {
        tokens.push_back(token);
    }
    if (tokens.front() == "..") {
        cdBack();
        tokens.erase(tokens.begin());
    } else goToRoot();
    
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
        std::string workdir;
        try {
            workdir = goToFolder(dirname);
        } catch (NoDirectoryExc e) {
            std::cerr << e.getWhat();
        }
        
        if (!workdir.empty() && !alreadyExists(workdir)) {
            Dir* tmp = new Dir(workdir,currentFolder);
            directories.push_back(tmp);
            currentFolder->addChild(tmp);
        } else if (!workdir.empty() && alreadyExists(workdir)){
            std::cerr << "This directory name is already taken. Please try again with another name!" << std::endl;
        }
        currentFolder = current;
        
    } else {
        if (!alreadyExists(dirname)) {
            Dir* tmp = new Dir(dirname, currentFolder);
            directories.push_back(tmp);
            currentFolder->addChild(tmp);
        } else std::cerr << "This directory name is already taken. Please try again with another name!" <<std::endl;
    }
}

void System::ls(std::string path) {
    if (path != "") {
        Dir* current = currentFolder;
        std::string working;
        try {
            working = goToFolder(path);
        } catch (NoDirectoryExc e) {
            std::cerr << e.getWhat();
        }
        
        //std::cout << working << currentFolder->getDirName() << std::endl;
        
        if (!working.empty()) {
            /*
            try {
                cd(working);
            } catch (NoDirectoryExc e) {
                std::cerr << e.getWhat();
            }
            */
            for (auto &d : directories) {
                //TODO: hiba üzenet ha nem létezik!!
                if (d->getName() == working && d->getParent()->getName() == currentFolder->getName()) {
                    d->listChildren();
                }
            }
        }
        currentFolder = current;
        
    } else {
        //TODO: hiba üzenet ha nem létezik!!
        for (auto &d : directories) {
            if (d->getName() == currentFolder->getName()) {
                d->listChildren();
            }
        }
    }
}

void System::cd(std::string dirname) {
    if (dirname.find("/") != std::string::npos) {
        std::stringstream ss(dirname);
        std::string token;
        while (getline(ss, token, '/')) {
            if (token == "..") cdBack();
            else cd(token);
            
        }
    } else {
        if (alreadyExists(dirname)) {
            for(Dir* &d : directories) {
                if (d->getName() == dirname && d->getParent() == currentFolder) {
                    currentFolder = d;
                }
            }
        } else {
            //std::cerr << "No directory found with the given name. Please try again with another name!" << std::endl;
            throw NoDirectoryExc();
        }
    }
}

void System::cdBack() {
	if (currentFolder->getParent() != nullptr) {
		for (auto &v : directories) {
			if (v->getName() == currentFolder->getName() && v->getParent()->getName() == currentFolder->getParent()->getName()) {
				currentFolder = dynamic_cast<Dir*>(v->getParent());
			}
		}
	}
	else { std::cerr << "You are in root!" << std::endl; }

}

void System::rm(std::string dirname) {
    if (dirname.find("/") != std::string::npos) {
        Dir* current = currentFolder;
        std::string workdir;
        
        try {
            workdir = goToFolder(dirname);
        } catch (NoDirectoryExc e) {
            std::cerr << e.getWhat();
        }
        
        if (!workdir.empty() && hasChildren(workdir)) {
            std::cerr << "This directory cannot be removed as it contains other directories/ files!\n";
        } else if (!workdir.empty() && !alreadyExists(workdir)) {
            std::cerr << "No directory found with the given name. Please try again with another name!" << std::endl;
        }
        else {
            for (unsigned i = 0; i < directories.size();i++) {
                if (directories[i]->getName() == workdir && directories[i]->getParent()->getName() == currentFolder->getName()) {
                    delete directories.at(i);
                    directories.erase(directories.begin() + i);
                }
            }
            
            for (unsigned i = 0; i< files.size();i++) {
                if (files[i]->getName() == workdir && directories[i]->getParent()->getName() == currentFolder->getName()) {
                    delete files.at(i);
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
            std::cerr << dirname << std::endl;
        }
        else {
            for (unsigned i = 0; i < directories.size();i++) {
                if (directories[i]->getName() == dirname && directories[i]->getParent()->getName() == currentFolder->getName()) {
                    directories.erase(directories.begin() + i);
                }
            }
            for (unsigned i = 0; i< files.size();i++) {
                if (files[i]->getName() == dirname && directories[i]->getParent()->getName() == currentFolder->getName()) {
                    files.erase(files.begin() + i);
                }
            }
        }
    }
}

void System::rmrf(std::string dirname) {
    if (dirname.find("/") != std::string::npos) {
        //std::cout << "helllo belloooo" << std::endl;
        Dir* current = currentFolder;
        std::string working;
        
        try {
            working = goToFolder(dirname);
        } catch (NoDirectoryExc e) {
            std::cerr << e.getWhat();
        }
        //std::cout << "helllo belloooo" << std::endl;
        if (!working.empty() && working != currentFolder->getName()) {
            while(hasChildren(working)) {
                cd(working);
                //std::cout << "helllo belloooo" << std::endl;
                rmrf(getChild(working));
                cdBack();
            }
            rm(working);
            //std::cout << "helllo belloooo" << std::endl;
        }
        currentFolder = current;
        //std::cout << "helllo belloooo" << std::endl;
    } else {
        if (dirname != currentFolder->getName()){
            while (hasChildren(dirname)) {
                cd(dirname);
                rmrf(getChild(dirname));
                cdBack();
            }
            rm(dirname);
        }
    }
}

void System::touch(std::string fname) {
    if (fname.find("/") != std::string::npos) {
        Dir* current = currentFolder;
        std::string working;
        
        try {
            working = goToFolder(fname);
        } catch (NoDirectoryExc e) {
            std::cerr << e.getWhat();
        }
        
        if (!working.empty()) {
            File* tmp = new File(working,currentFolder);
            files.push_back(tmp);
            currentFolder->addChild(tmp);
        }
        currentFolder = current;
        
    } else {
        if (!alreadyExists(fname)) {
            File* tmp = new File(fname,currentFolder);
            files.push_back(tmp);
            currentFolder->addChild(tmp);
        } else std::cerr << "This file name is already taken. Please try again with another name!" <<std::endl;
    }
}
