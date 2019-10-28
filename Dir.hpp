#pragma	once

#include "Node.hpp"
#include "File.hpp"
#include <string>
#include <iostream>
#include <vector>

class Dir : public Node{
private:
    std::vector<Node*> children;
public:
    Dir(std::string, Dir*);
    void addChild(Node*);
    void listChildren();
};
