#include "System.hpp"
#include <sstream>

System::System() {
    currentFolder = new Dir("root", nullptr);
};

System::~System(){

}

Dir* System::getCurrentFolder() {
    return currentFolder;
}

Node* System::getChild(Dir* dir) const {
    if (!dir->getChildren().empty()) {
        return dir->getChildren().at(0);
    }
    return nullptr;
}

Node* System::stringToNode(std::string name) {
    for (auto &n : currentFolder->getChildren()) {
        if (n->getName() == name) {
            return n;
        }
    }
    return nullptr;
}

void System::printCore() const {
	std::cout << "gabor-mbp:" << currentFolder->getName() << " gabor$ ";
}

bool System::alreadyExists(std::string name) const {
    for (auto &d : currentFolder->getChildren()) {
        if (d->getName() == name) {
            return true;
        }
    }
    return false;
}

bool System::hasChildren(Dir* dir) const {
    if (!dir->getChildren().empty()) {
        return true;
    }
    return false;
}

void System::goToRoot(){
    while (currentFolder->getParent() != nullptr) {
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
        
        Dir* tmp = new Dir(workdir,currentFolder);
        
        if (!workdir.empty() && !alreadyExists(workdir)) {
            currentFolder->addChild(tmp);
        } else std::cerr << "This directory name is already taken. Please try again with another name!" <<std::endl;
        
        currentFolder = current;
    } else {
        Dir* tmp = new Dir(dirname, currentFolder);
        if (!alreadyExists(dirname)) {
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
        if (!working.empty()) {
            try {
                cd(working);
            } catch (NoDirectoryExc e) {
                std::cout << e.getWhat();
            }
            currentFolder->listChildren();
        }
        currentFolder = current;
        
    } else {
        currentFolder->listChildren();
    }
}

void System::cd(std::string dirname) {
    if (dirname.find("/") != std::string::npos) {
        std::string working;
        try {
            working = goToFolder(dirname);
        } catch (NoDirectoryExc e) {
            std::cerr << e.getWhat();
        }
        
        if (!working.empty() && alreadyExists(working)) {
            cd(working);
        }
    } else {
        if (alreadyExists(dirname)  ) {
            for (auto &n : currentFolder->getChildren()) {
                if (dynamic_cast<Dir*>(n) && n->getName() == dirname) {
                    currentFolder = dynamic_cast<Dir*>(n);
                }
            }
        } else throw NoDirectoryExc();
    }
}

void System::cdBack() {
    if (currentFolder->getParent() != nullptr) {
        currentFolder = dynamic_cast<Dir*>(currentFolder->getParent());
    } else std::cerr << "You are in root!" << std::endl;
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
        
        
        if (Dir* workingDir = dynamic_cast<Dir*>(stringToNode(workdir))) {
            if (hasChildren(workingDir)) {
                std::cerr << "This directory cannot be removed as it contains other directories/ files!\n";
            }
        }
        if (!alreadyExists(workdir)) {
            std::cerr << "No directory or file found with the given name. Please try again with another name!" << std::endl;
        } else {
            std::vector<Node*> tmp = currentFolder->getChildren();
            for (unsigned i = 0; i < tmp.size(); i++) {
                if (tmp[i]->getName() == workdir) {
                    tmp.erase(tmp.begin() + i);
                }
            }
            currentFolder->setChildren(tmp);
            currentFolder = current;
        }
    }
    else {
        if (Dir* work = dynamic_cast<Dir*>(stringToNode(dirname))) {
            if (hasChildren(work)) std::cerr << "This directory cannot be removed as it contains other directories/ files!\n";
        }

        if (!alreadyExists(dirname)) {
            std::cerr << "No directory or file found with the given name. Please try again with another name!" << std::endl;
        } else {
            std::vector<Node*> tmp = currentFolder->getChildren();
            for (unsigned i = 0; i < tmp.size(); i++) {
                if (tmp[i]->getName() == dirname) {
                    tmp.erase(tmp.begin() + i);
                }
            }
            currentFolder->setChildren(tmp);
        }
    }
}

void System::rmrf(std::string dirname) {
    if (dirname.find("/") != std::string::npos) {
        Dir* current = currentFolder;
        std::string working;
        
        try {
            working = goToFolder(dirname);
        } catch (NoDirectoryExc e) {
            std::cerr << e.getWhat();
        }
        
        if (Dir* work = dynamic_cast<Dir*>(stringToNode(working))) {
            while (hasChildren(work)) {
                cd(working);
                rmrf(currentFolder->getChild()->getName());
                cdBack();
            }
            rm(working);
        } else {
            rm(working);
        }
        
        
        currentFolder = current;
    } else {
        if (Dir* work = dynamic_cast<Dir*>(stringToNode(dirname))) {
            while (hasChildren(work)) {
                cd(dirname);
                rmrf(work->getChild()->getName());
                cdBack();
            }
            rm(dirname);
        } else {
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
        
        if (!working.empty() && !alreadyExists(working)) {
            currentFolder->addChild(new File(working,currentFolder));
        }
        currentFolder = current;
        
    } else {
        if (!alreadyExists(fname)) {
            currentFolder->addChild(new File(fname,currentFolder));
        } else std::cerr << "This file name is already taken. Please try again with another name!" <<std::endl;
    }
}

void System::echo(std::string content, std::string fname) {
	if (fname.find("/") != std::string::npos) {
		Dir* current = currentFolder;
		std::string working;

		try {
			working = goToFolder(fname);
		}
		catch (NoDirectoryExc e) {
			std::cerr << e.getWhat() << std::endl;
		}

		if (!working.empty() && !alreadyExists(working)) {
			currentFolder->addChild(new File(working, currentFolder, content));
		}
		else if (!working.empty() && alreadyExists(working)) {
			dynamic_cast<File*>(stringToNode(working))->setContent(content);
		}
		else std::cerr << "You need to enter a filename after the content!" << std::endl;
		currentFolder = current;

	}
	else {
		if (!fname.empty()) {
			if (!alreadyExists(fname)) {
				currentFolder->addChild(new File(fname, currentFolder, content));
			}
			else {
				for (auto &f : currentFolder->getChildren()) {
					if (dynamic_cast<File*>(f) != nullptr && f->getName() == fname && f->getParent() == currentFolder) {
						dynamic_cast<File*>(f)->setContent(content);
					}
				}
			}
		}
		else std::cerr << "You need to enter a filename after the content!" << std::endl;
	}
}
