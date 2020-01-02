#pragma	once

#include "Node.hpp"
#include <string>
#include <iostream>
#include <vector>
/** @brief Class for describing folders. */
class Dir : public Node{
private:
    /**
     * This stores the other elements in the folder.
    */
    std::vector<Node*> children;
public:
    /**
     * @param name Sets the folder's name.
     * @param parent Sets the folder's parent.
    */
    Dir(std::string name, Dir* parent);
    /**
     * @brief Get function for the folder's content.
     * 
     * @return Vector that contains the children.
    */
    std::vector<Node*> getChildren();
    /**
     * @brief Returns a child from the children vector.
     * 
     * @return Node* - Return the first element of the children vector.
     * @return Nullptr - If the children vector is empty.
    */
    Node* getChild();

    /**
     * @brief Set function for the children vector.
     * 
     * @param vector Sets the given vector to the children vector of the class.
    */
    void setChildren(std::vector<Node*> vector);
    
    /**
     * @brief Giving a Node pointer to the children vector.
     * 
     * @param child Gives this parameter to the children vector of the folder.
    */
    void addChild(Node* child);
    /**
     * Listing every element of the children vector on std::cout.
    */
    void listChildren();

    /**
     * @brief Tests if the given folder has a children.
     * 
     * @return true - if the children vector contains at least 1 element.
     * @return false - if the children vector is empty.
    */
    bool hasChildren();
};
