//
//  Node.cpp
//  Terminal
//
//  Created by Gábor Horváth on 2019. 10. 28..
//  Copyright © 2019. Gábor Horváth. All rights reserved.
//

#include "Node.hpp"


Node::Node(std::string name, Node *parent): name(name), parent(parent) {}

Node *Node::getParent() const {
    return parent;
}

std::string Node::getName() const {
    return name;
}
