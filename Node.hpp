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

/**
 * Parent class for handling files and folders
*/
class Node {
private:
    std::string name;
    Node* parent;
public:
    /**
     * @param name sets the node's name
     * @param parent sets the node's parent folder
    */
    Node(std::string name, Node* parent);
    /**
     * Get function for the parent folder's pointer
    */
    Node* getParent() const;
    /**
     * Get function for the Node name
    */
    std::string getName() const;
    /**
     * Only needed for polymorphism
    */
    virtual ~Node() = default;
    
};

#endif /* Node_hpp */
