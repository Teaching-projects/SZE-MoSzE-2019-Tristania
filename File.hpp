#ifndef File_hpp
#define File_hpp

#include <stdio.h>
#include <string>
#include "Node.hpp"
#include "Dir.hpp"

class File : public Node {
    std::string name;
    Dir* parent;
    std::string content;
public:
    File(std::string, Dir*,std::string="");
    std::string getName();
    Dir* getParent();
    std::string getContent();
    void setContent(std::string);
};

#endif /* File_hpp */
