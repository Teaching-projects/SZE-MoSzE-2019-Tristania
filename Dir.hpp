#pragma	once

#include "Node.hpp"
#include <string>
#include <iostream>
#include <vector>

class Dir : public Node{
private:
    std::vector<Node*> children;
public:
    Dir(std::string, Dir*);
    std::vector<Node*> getChildren();
    Node* getChild();
    void setChildren(std::vector<Node*>);
    bool hasChildren() const;
    Node* getChild() const;
    void addChild(Node*);
    void listChildren();
};
