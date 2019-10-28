//
//  Node.hpp
//  Terminal
//
//  Created by Gábor Horváth on 2019. 10. 28..
//  Copyright © 2019. Gábor Horváth. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp

#include <stdio.h>
#include <string>


class Node {
private:
    std::string name;
    Node* parent;
public:
    Node(std::string, Node*);
    Node* getParent() const;
    std::string getName() const;
    virtual ~Node() = default; //csak a polimorfizmus végett
    
};

#endif /* Node_hpp */
