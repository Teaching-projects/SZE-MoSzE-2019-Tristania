#include "Dir.hpp"

Dir::Dir(std::string name, Dir* parent): Node(name, parent) {}


void Dir::addChild(Node* param) {
    children.push_back(param);
}

void Dir::listChildren() {
    for (auto &d : children) {
        if (dynamic_cast<Dir*>(d)) {
            std::cout << d->getName() << "/" << std::endl;
        } else if (dynamic_cast<File*>(d)) {
            std::cout << d->getName() << std::endl;
        }
    }
}

