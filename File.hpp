#ifndef File_hpp
#define File_hpp

#include <stdio.h>
#include <string>
#include "Node.hpp"
#include "Dir.hpp"

/**
 * @brief Class for describing files.
 * @details this class is used to store files.
*/
class File : public Node {
    std::string name;
    Dir* parent;
    std::string content;
public:
    /**
     * @brief Constructor for the File class.
     * 
     * @param name file's name.
     * @param parent pointer of the folder that contains the file.
     * @param content content of the file.
    */
    File(std::string name, Dir* parent, std::string content="");
    /**
     * Get function for the file's name.
    */
    std::string getName();
    /**
     * Get function for the pointer of the file's parent.
    */
    Dir* getParent();
    /**
     * Get function for the file's content.
    */
    std::string getContent();
    /**
     * Set function that sets the file's content.
     * @param content Sets the given string as the file's content.
    */
    void setContent(std::string content);
};

#endif /* File_hpp */
