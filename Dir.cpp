#include "Dir.hpp"

Dir::Dir(std::string name, Dir* parent): Node(name, parent) {}

std::vector<Node*> Dir::getChildren() { return children; }

Node* Dir::getChild() {
    return children.at(0);
}

void Dir::setChildren(std::vector<Node*> pchildren) {
    children = pchildren;
}

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

